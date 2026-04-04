# ae-mcp-server

An MCP (Model Context Protocol) server that lets **Claude Code** control **Adobe After Effects** via ExtendScript.

## How it works

```
Claude Code  ←──MCP stdio──→  ae-mcp-server  ──-r flag──→  After Effects (ExtendScript)
```

The server runs as a local Node.js process. When Claude calls a tool, the server writes a temporary `.jsx` script, passes it to After Effects using the `-r` CLI flag, and reads back the result.

---

## Requirements

- Node.js ≥ 18 (ESM support)
- Adobe After Effects CC 2018 or later (with scripting enabled)
- After Effects must have **"Allow Scripts to Write Files and Access Network"** enabled:
  `After Effects → Edit → Preferences → Scripting & Expressions → Allow Scripts to Write Files and Access Network`

---

## Installation

```bash
cd ae-mcp-server
npm install
```

---

## Register with Claude Code

Edit your Claude Code configuration file.

**macOS / Linux** → `~/.claude.json`  
**Windows** → `%APPDATA%\Claude\claude.json`

Add the server under `mcpServers`:

```json
{
  "mcpServers": {
    "after-effects": {
      "command": "node",
      "args": ["/absolute/path/to/ae-mcp-server/index.js"]
    }
  }
}
```

Replace `/absolute/path/to/ae-mcp-server/` with the real path on your machine.

---

## Configuration (environment variables)

| Variable | Default | Description |
|----------|---------|-------------|
| `AE_EXECUTABLE` | Auto-detected | Full path to the After Effects executable |
| `AE_SCRIPT_TIMEOUT` | `30000` | Milliseconds to wait for AE to execute a script |

You can pass env vars through the Claude config:

```json
{
  "mcpServers": {
    "after-effects": {
      "command": "node",
      "args": ["/path/to/ae-mcp-server/index.js"],
      "env": {
        "AE_EXECUTABLE": "/Applications/Adobe After Effects 2024/Adobe After Effects 2024.app/Contents/MacOS/After Effects",
        "AE_SCRIPT_TIMEOUT": "60000"
      }
    }
  }
}
```

---

## Available tools

| Tool | Description |
|------|-------------|
| `run_ae_script` | Execute arbitrary ExtendScript (JSX) in After Effects |
| `get_project_info` | Get info about the currently open project |
| `list_compositions` | List all compositions |
| `get_composition_info` | Detailed info + layer list for a composition |
| `create_composition` | Create a new composition |
| `add_text_layer` | Add a text layer with font size, position, and colour |
| `add_solid_layer` | Add a solid colour layer |
| `add_effect` | Apply an effect to a layer |
| `set_keyframe` | Set a keyframe on any layer property |
| `get_layer_properties` | Read Transform properties at a given time |
| `render_composition` | Render a comp to disk via the Render Queue |
| `save_project` | Save (or Save As) the current project |
| `open_project` | Open a `.aep` project file |

---

## Example prompts for Claude

Once registered, you can ask Claude things like:

- *"Create a 1920×1080 composition called 'Intro' at 30fps for 5 seconds."*
- *"Add white text 'Hello World' at font size 96 to the 'Intro' composition."*
- *"Set a keyframe on position at t=0 of [960, 540] and another at t=2 of [960, 200] on the text layer."*
- *"Add a Gaussian Blur effect to the text layer."*
- *"Render the 'Intro' comp to /Users/me/Desktop/intro.mov."*
- *"Run this JSX: `app.project.activeItem.name`"* (returns the active comp name)

---

## After Effects executable paths (defaults)

**macOS**
```
/Applications/Adobe After Effects <YEAR>/Adobe After Effects <YEAR>.app/Contents/MacOS/After Effects
```

**Windows**
```
C:\Program Files\Adobe\Adobe After Effects <YEAR>\Support Files\AfterFX.exe
```

Set `AE_EXECUTABLE` if your installation is in a non-standard location.

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| `After Effects execution failed` | Check that `AE_EXECUTABLE` points to the correct binary |
| Scripts run but AE shows permission errors | Enable "Allow Scripts to Write Files and Access Network" in AE preferences |
| Timeout errors on render | Increase `AE_SCRIPT_TIMEOUT` (renders can take a long time) |
| `ERROR: …` in tool output | The ExtendScript itself threw — check the script syntax / API usage |
