#!/usr/bin/env node
/**
 * MCP Server – Adobe After Effects bridge
 *
 * Exposes After Effects scripting tools to Claude Code via the
 * Model Context Protocol (MCP). Scripts are delivered to AE using
 * the `afterfx -r <script.jsx>` CLI approach, which works on macOS
 * and Windows with After Effects CC 2018+.
 *
 * Setup
 * -----
 * 1.  Install:  npm install   (inside ae-mcp-server/)
 * 2.  Register in Claude Code — edit ~/.claude.json:
 *       {
 *         "mcpServers": {
 *           "after-effects": {
 *             "command": "node",
 *             "args": ["/absolute/path/to/ae-mcp-server/index.js"]
 *           }
 *         }
 *       }
 * 3.  (Optional) Set the AE_EXECUTABLE env var if AE is in a non-default location.
 *     (Optional) Set AE_SCRIPT_TIMEOUT (ms) to change the execution timeout (default 30 000).
 */

import { McpServer } from "@modelcontextprotocol/sdk/server/mcp.js";
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js";
import { z } from "zod";
import { execFile } from "node:child_process";
import { promisify } from "node:util";
import * as fs from "node:fs";
import * as os from "node:os";
import * as path from "node:path";

const execFileAsync = promisify(execFile);

// ---------------------------------------------------------------------------
// Configuration
// ---------------------------------------------------------------------------

/**
 * Resolve the After Effects executable.
 * Priority: AE_EXECUTABLE env var → platform-specific defaults.
 */
function resolveAeExecutable() {
  if (process.env["AE_EXECUTABLE"]) {
    return process.env["AE_EXECUTABLE"];
  }
  if (process.platform === "darwin") {
    const candidates = [
      "/Applications/Adobe After Effects 2025/Adobe After Effects 2025.app/Contents/MacOS/After Effects",
      "/Applications/Adobe After Effects 2024/Adobe After Effects 2024.app/Contents/MacOS/After Effects",
      "/Applications/Adobe After Effects 2023/Adobe After Effects 2023.app/Contents/MacOS/After Effects",
      "/Applications/Adobe After Effects 2022/Adobe After Effects 2022.app/Contents/MacOS/After Effects",
    ];
    for (const c of candidates) {
      if (fs.existsSync(c)) return c;
    }
    return candidates[0];
  }
  if (process.platform === "win32") {
    const candidates = [
      "C:\\Program Files\\Adobe\\Adobe After Effects 2025\\Support Files\\AfterFX.exe",
      "C:\\Program Files\\Adobe\\Adobe After Effects 2024\\Support Files\\AfterFX.exe",
      "C:\\Program Files\\Adobe\\Adobe After Effects 2023\\Support Files\\AfterFX.exe",
      "C:\\Program Files\\Adobe\\Adobe After Effects 2022\\Support Files\\AfterFX.exe",
    ];
    for (const c of candidates) {
      if (fs.existsSync(c)) return c;
    }
    return candidates[0];
  }
  return "afterfx";
}

const AE_EXECUTABLE = resolveAeExecutable();
const SCRIPT_TIMEOUT_MS = Number(process.env["AE_SCRIPT_TIMEOUT"] ?? 30_000);

// ---------------------------------------------------------------------------
// ExtendScript runner
// ---------------------------------------------------------------------------

/**
 * Write `jsxCode` to a temp file, run it in After Effects via `-r`, and
 * return whatever the script wrote to the companion result file.
 *
 * The wrapper function captures the return value of `jsxCode` and writes it
 * to a sidecar `.txt` file so Node can read it back after AE exits.
 */
async function runExtendScript(jsxCode) {
  const tmpDir = os.tmpdir();
  const id = `ae_mcp_${Date.now()}_${Math.random().toString(36).slice(2)}`;
  const scriptPath = path.join(tmpDir, `${id}.jsx`);
  const resultPath = path.join(tmpDir, `${id}_result.txt`);

  const wrappedCode = `
(function () {
  var _resultFile = new File("${resultPath.replace(/\\/g, "\\\\")}");
  try {
    var _result = (function () {
${jsxCode}
    })();
    _resultFile.open("w");
    _resultFile.write(_result !== undefined ? String(_result) : "OK");
    _resultFile.close();
  } catch (e) {
    _resultFile.open("w");
    _resultFile.write("ERROR: " + e.toString());
    _resultFile.close();
  }
})();
`;

  fs.writeFileSync(scriptPath, wrappedCode, "utf-8");

  try {
    await execFileAsync(AE_EXECUTABLE, ["-r", scriptPath], {
      timeout: SCRIPT_TIMEOUT_MS,
    });
  } catch (err) {
    // AE may exit non-zero even on success; only throw if no result file.
    if (!fs.existsSync(resultPath)) {
      throw new Error(
        `After Effects execution failed: ${err instanceof Error ? err.message : String(err)}`
      );
    }
  } finally {
    try { fs.unlinkSync(scriptPath); } catch { /* ignore */ }
  }

  if (!fs.existsSync(resultPath)) {
    throw new Error(
      "After Effects did not produce a result. " +
        `Ensure AE is installed and the executable path is correct (current: ${AE_EXECUTABLE}). ` +
        "Override with the AE_EXECUTABLE environment variable if needed."
    );
  }

  const result = fs.readFileSync(resultPath, "utf-8");
  try { fs.unlinkSync(resultPath); } catch { /* ignore */ }

  if (result.startsWith("ERROR:")) {
    throw new Error(result);
  }
  return result;
}

// ---------------------------------------------------------------------------
// MCP Server
// ---------------------------------------------------------------------------

const server = new McpServer({
  name: "after-effects",
  version: "1.0.0",
});

// ── run_ae_script ───────────────────────────────────────────────────────────
server.tool(
  "run_ae_script",
  "Execute arbitrary ExtendScript (JSX) code inside Adobe After Effects and return the result.",
  {
    script: z
      .string()
      .min(1)
      .describe(
        "ExtendScript (JavaScript ES3) code to run inside After Effects. " +
          "The return value of the last expression is captured. " +
          "Use `app`, `app.project`, `app.project.activeItem`, etc."
      ),
  },
  async ({ script }) => {
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── get_project_info ────────────────────────────────────────────────────────
server.tool(
  "get_project_info",
  "Get information about the currently open After Effects project.",
  {},
  async () => {
    const script = `
var proj = app.project;
if (!proj) return "No project open";
var info = {
  name: proj.file ? proj.file.name : "(unsaved)",
  path: proj.file ? proj.file.fsName : "",
  numItems: proj.numItems,
  bitsPerChannel: proj.bitsPerChannel,
  linearBlending: proj.linearBlending
};
return JSON.stringify(info, null, 2);
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── list_compositions ───────────────────────────────────────────────────────
server.tool(
  "list_compositions",
  "List all compositions in the currently open After Effects project.",
  {},
  async () => {
    const script = `
var comps = [];
for (var i = 1; i <= app.project.numItems; i++) {
  var item = app.project.item(i);
  if (item instanceof CompItem) {
    comps.push({
      index: i,
      name: item.name,
      duration: item.duration,
      frameRate: item.frameRate,
      width: item.width,
      height: item.height,
      numLayers: item.numLayers
    });
  }
}
return JSON.stringify(comps, null, 2);
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── get_composition_info ────────────────────────────────────────────────────
server.tool(
  "get_composition_info",
  "Get detailed information about a specific composition by name.",
  {
    comp_name: z.string().min(1).describe("Exact name of the composition"),
  },
  async ({ comp_name }) => {
    const safe = comp_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const script = `
var comp = null;
for (var i = 1; i <= app.project.numItems; i++) {
  if (app.project.item(i).name === "${safe}" && app.project.item(i) instanceof CompItem) {
    comp = app.project.item(i);
    break;
  }
}
if (!comp) return "Composition not found: ${safe}";
var layers = [];
for (var j = 1; j <= comp.numLayers; j++) {
  var layer = comp.layer(j);
  layers.push({
    index: j,
    name: layer.name,
    type: layer.constructor.name,
    enabled: layer.enabled,
    inPoint: layer.inPoint,
    outPoint: layer.outPoint,
    startTime: layer.startTime
  });
}
var info = {
  name: comp.name,
  duration: comp.duration,
  frameRate: comp.frameRate,
  width: comp.width,
  height: comp.height,
  pixelAspect: comp.pixelAspect,
  bgColor: comp.bgColor,
  numLayers: comp.numLayers,
  layers: layers
};
return JSON.stringify(info, null, 2);
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── create_composition ──────────────────────────────────────────────────────
server.tool(
  "create_composition",
  "Create a new composition in the currently open After Effects project.",
  {
    name: z.string().min(1).describe("Name for the new composition"),
    width: z.number().int().positive().default(1920).describe("Width in pixels"),
    height: z.number().int().positive().default(1080).describe("Height in pixels"),
    frame_rate: z.number().positive().default(24).describe("Frame rate (fps)"),
    duration: z.number().positive().default(10).describe("Duration in seconds"),
    bg_color: z
      .tuple([z.number(), z.number(), z.number()])
      .default([0, 0, 0])
      .describe("Background color as [R, G, B] where each component is 0–1"),
  },
  async ({ name, width, height, frame_rate, duration, bg_color }) => {
    const safe = name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const [r, g, b] = bg_color;
    const script = `
var comp = app.project.items.addComp("${safe}", ${width}, ${height}, 1, ${duration}, ${frame_rate});
comp.bgColor = [${r}, ${g}, ${b}];
return "Created composition: " + comp.name + " (" + comp.width + "x" + comp.height + " @ " + comp.frameRate + "fps, " + comp.duration + "s)";
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── add_text_layer ──────────────────────────────────────────────────────────
server.tool(
  "add_text_layer",
  "Add a text layer to a composition.",
  {
    comp_name: z.string().min(1).describe("Target composition name"),
    text: z.string().min(1).describe("Text content"),
    font_size: z.number().positive().default(72).describe("Font size in pixels"),
    position_x: z.number().default(960).describe("X position in pixels"),
    position_y: z.number().default(540).describe("Y position in pixels"),
    color: z
      .tuple([z.number(), z.number(), z.number()])
      .default([1, 1, 1])
      .describe("Text color as [R, G, B] where each component is 0–1"),
  },
  async ({ comp_name, text, font_size, position_x, position_y, color }) => {
    const safeComp = comp_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeText = text
      .replace(/\\/g, "\\\\")
      .replace(/"/g, '\\"')
      .replace(/\n/g, "\\n");
    const [r, g, b] = color;
    const script = `
var comp = null;
for (var i = 1; i <= app.project.numItems; i++) {
  if (app.project.item(i).name === "${safeComp}" && app.project.item(i) instanceof CompItem) {
    comp = app.project.item(i);
    break;
  }
}
if (!comp) return "Composition not found: ${safeComp}";
var textLayer = comp.layers.addText("${safeText}");
var textProp = textLayer.property("Source Text");
var textDoc = textProp.value;
textDoc.fontSize = ${font_size};
textDoc.fillColor = [${r}, ${g}, ${b}];
textDoc.justification = ParagraphJustification.CENTER_JUSTIFY;
textProp.setValue(textDoc);
textLayer.property("Transform").property("Position").setValue([${position_x}, ${position_y}]);
return "Added text layer: " + textLayer.name;
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── add_solid_layer ─────────────────────────────────────────────────────────
server.tool(
  "add_solid_layer",
  "Add a solid colour layer to a composition.",
  {
    comp_name: z.string().min(1).describe("Target composition name"),
    layer_name: z.string().min(1).describe("Name for the solid layer"),
    width: z.number().int().positive().default(1920).describe("Width in pixels"),
    height: z.number().int().positive().default(1080).describe("Height in pixels"),
    color: z
      .tuple([z.number(), z.number(), z.number()])
      .default([0.2, 0.2, 0.2])
      .describe("Layer color as [R, G, B] where each component is 0–1"),
  },
  async ({ comp_name, layer_name, width, height, color }) => {
    const safeComp = comp_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeName = layer_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const [r, g, b] = color;
    const script = `
var comp = null;
for (var i = 1; i <= app.project.numItems; i++) {
  if (app.project.item(i).name === "${safeComp}" && app.project.item(i) instanceof CompItem) {
    comp = app.project.item(i);
    break;
  }
}
if (!comp) return "Composition not found: ${safeComp}";
var solid = comp.layers.addSolid([${r}, ${g}, ${b}], "${safeName}", ${width}, ${height}, 1);
return "Added solid layer: " + solid.name;
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── add_effect ──────────────────────────────────────────────────────────────
server.tool(
  "add_effect",
  "Add an effect to a layer in a composition.",
  {
    comp_name: z.string().min(1).describe("Target composition name"),
    layer_name: z.string().min(1).describe("Target layer name"),
    effect_name: z
      .string()
      .min(1)
      .describe(
        "Effect name as shown in After Effects (e.g. 'Gaussian Blur', 'Hue/Saturation', 'Drop Shadow')"
      ),
  },
  async ({ comp_name, layer_name, effect_name }) => {
    const safeComp = comp_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeLayer = layer_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeEffect = effect_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const script = `
var comp = null;
for (var i = 1; i <= app.project.numItems; i++) {
  if (app.project.item(i).name === "${safeComp}" && app.project.item(i) instanceof CompItem) {
    comp = app.project.item(i); break;
  }
}
if (!comp) return "Composition not found: ${safeComp}";
var layer = comp.layer("${safeLayer}");
if (!layer) return "Layer not found: ${safeLayer}";
var effect = layer.property("Effects").addProperty("${safeEffect}");
if (!effect) return "Effect not found: ${safeEffect}";
return "Added effect '" + effect.name + "' to layer '" + layer.name + "'";
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── set_keyframe ────────────────────────────────────────────────────────────
server.tool(
  "set_keyframe",
  "Set a keyframe on a layer property.",
  {
    comp_name: z.string().min(1).describe("Target composition name"),
    layer_name: z.string().min(1).describe("Target layer name"),
    property_path: z
      .string()
      .min(1)
      .describe(
        "Dot-separated property path, e.g. 'Transform.Position' or 'Transform.Opacity'"
      ),
    time: z.number().min(0).describe("Time in seconds"),
    value: z
      .union([z.number(), z.array(z.number()), z.string()])
      .describe("Keyframe value: a number, an [x,y] or [x,y,z] array, or a string"),
  },
  async ({ comp_name, layer_name, property_path, time, value }) => {
    const safeComp = comp_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeLayer = layer_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const parts = property_path
      .split(".")
      .map((p) => `property("${p.replace(/\\/g, "\\\\").replace(/"/g, '\\"')}")`);
    const propChain = parts.join(".");
    const valueStr = JSON.stringify(value);
    const script = `
var comp = null;
for (var i = 1; i <= app.project.numItems; i++) {
  if (app.project.item(i).name === "${safeComp}" && app.project.item(i) instanceof CompItem) {
    comp = app.project.item(i); break;
  }
}
if (!comp) return "Composition not found: ${safeComp}";
var layer = comp.layer("${safeLayer}");
if (!layer) return "Layer not found: ${safeLayer}";
var prop = layer.${propChain};
if (!prop) return "Property not found: ${property_path}";
prop.setValueAtTime(${time}, ${valueStr});
return "Keyframe set on '${property_path}' at t=" + ${time} + "s";
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── get_layer_properties ────────────────────────────────────────────────────
server.tool(
  "get_layer_properties",
  "Get Transform properties (position, scale, rotation, opacity) of a layer at a given time.",
  {
    comp_name: z.string().min(1).describe("Target composition name"),
    layer_name: z.string().min(1).describe("Target layer name"),
    time: z.number().min(0).default(0).describe("Time in seconds to sample"),
  },
  async ({ comp_name, layer_name, time }) => {
    const safeComp = comp_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeLayer = layer_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const script = `
var comp = null;
for (var i = 1; i <= app.project.numItems; i++) {
  if (app.project.item(i).name === "${safeComp}" && app.project.item(i) instanceof CompItem) {
    comp = app.project.item(i); break;
  }
}
if (!comp) return "Composition not found: ${safeComp}";
var layer = comp.layer("${safeLayer}");
if (!layer) return "Layer not found: ${safeLayer}";
var t = layer.property("Transform");
var props = {
  anchorPoint: t.property("Anchor Point").valueAtTime(${time}, false),
  position:    t.property("Position").valueAtTime(${time}, false),
  scale:       t.property("Scale").valueAtTime(${time}, false),
  rotation:    t.property("Rotation").valueAtTime(${time}, false),
  opacity:     t.property("Opacity").valueAtTime(${time}, false)
};
return JSON.stringify(props, null, 2);
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── render_composition ──────────────────────────────────────────────────────
server.tool(
  "render_composition",
  "Add a composition to the Render Queue and render it.",
  {
    comp_name: z.string().min(1).describe("Name of the composition to render"),
    output_path: z
      .string()
      .min(1)
      .describe("Full output file path including extension (e.g. /Users/me/Desktop/output.mp4)"),
    output_module: z
      .string()
      .default("Lossless")
      .describe(
        "Output module template (e.g. 'Lossless', 'H.264 - Match Render Settings - 15 Mbps')"
      ),
  },
  async ({ comp_name, output_path, output_module }) => {
    const safeComp = comp_name.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeOut = output_path.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const safeMod = output_module.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const script = `
var comp = null;
for (var i = 1; i <= app.project.numItems; i++) {
  if (app.project.item(i).name === "${safeComp}" && app.project.item(i) instanceof CompItem) {
    comp = app.project.item(i); break;
  }
}
if (!comp) return "Composition not found: ${safeComp}";
var rqItem = app.project.renderQueue.items.add(comp);
var om = rqItem.outputModule(1);
om.applyTemplate("${safeMod}");
om.file = new File("${safeOut}");
app.project.renderQueue.render();
return "Render complete: ${safeOut}";
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── save_project ────────────────────────────────────────────────────────────
server.tool(
  "save_project",
  "Save the currently open After Effects project.",
  {
    save_as: z
      .string()
      .optional()
      .describe(
        "Optional full path to save to a new file (Save As). If omitted, performs a plain Save."
      ),
  },
  async ({ save_as }) => {
    let script;
    if (save_as) {
      const safePath = save_as.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
      script = `
var f = new File("${safePath}");
app.project.save(f);
return "Project saved to: " + f.fsName;
`;
    } else {
      script = `
if (!app.project.file) return "Project has never been saved; provide a save_as path.";
app.project.save();
return "Project saved: " + app.project.file.fsName;
`;
    }
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ── open_project ────────────────────────────────────────────────────────────
server.tool(
  "open_project",
  "Open an After Effects project file (.aep).",
  {
    project_path: z
      .string()
      .min(1)
      .describe("Absolute path to the .aep file"),
  },
  async ({ project_path }) => {
    const safePath = project_path.replace(/\\/g, "\\\\").replace(/"/g, '\\"');
    const script = `
var f = new File("${safePath}");
if (!f.exists) return "File not found: ${safePath}";
app.open(f);
return "Opened project: " + app.project.file.name;
`;
    const result = await runExtendScript(script);
    return { content: [{ type: "text", text: result }] };
  }
);

// ---------------------------------------------------------------------------
// Start
// ---------------------------------------------------------------------------

const transport = new StdioServerTransport();
await server.connect(transport);
process.stderr.write(`[ae-mcp-server] running. AE executable: ${AE_EXECUTABLE}\n`);
