# FileOrganizer Web Interface

A beautiful, modern web interface for the FileOrganizer C++ application. This provides an intuitive graphical frontend while leveraging your existing command-line tool.

## ✨ Features

- **Modern UI**: Clean, responsive design that works on all devices
- **Real-time Progress**: Visual progress indicators for all operations
- **File Preview**: See what will be organized before making changes
- **Organization History**: View and manage past organization sessions
- **Smart Undo**: Selective undo with session-based restoration
- **Quick Access**: One-click access to common folders (Downloads, Desktop, Documents)
- **Cross-Platform**: Works on Windows, macOS, and Linux
- **No Dependencies**: Uses only Node.js built-in modules

## 🚀 Quick Start

### Prerequisites

- Node.js (any recent version)
- Built FileOrganizer executable (`build/FileOrganizer.exe` on Windows or `build/FileOrganizer` on Linux/macOS)

### Installation & Setup

1. **Build the C++ application first** (if you haven't already):

   ```bash
   # Windows
   build.bat

   # Linux/macOS
   ./run.sh
   ```

2. **Start the web interface**:

   ```bash
   # Windows
   cd web
   start.bat

   # Linux/macOS
   cd web
   chmod +x start.sh
   ./start.sh
   ```

3. **Open your browser** to `http://localhost:3000` (should open automatically)

## 🖥️ Usage

### Basic Workflow

1. **Enter Folder Path**: Type the path to the folder you want to organize
2. **Preview First**: Click "Preview Files" to see what will be organized
3. **Organize**: Click "Organize Files" to apply the changes
4. **Track History**: Use "History" to view past operations
5. **Undo if Needed**: Use "Undo Last" to restore files to their original locations

### Interface Elements

#### 📂 Folder Selection

- **Manual Entry**: Type the full path to your folder
- **Quick Access**: Click Downloads, Desktop, or Documents for instant selection
- **Browse Button**: Future enhancement for file system navigation

#### 🚀 Action Buttons

- **👁️ Preview Files**: Shows what files will be moved where (safe, no changes made)
- **📋 Organize Files**: Performs the actual organization (creates folders and moves files)
- **📊 History**: Shows all past organization sessions for the selected folder
- **↩️ Undo Last**: Reverses the most recent organization operation

#### 📋 Results Section

- Displays output from the FileOrganizer executable
- Shows detailed information about processed files
- Includes error messages and status updates

#### ⏳ Progress Tracking

- Real-time progress bar for long operations
- Status updates during file processing
- Visual feedback for all operations

### Advanced Features

#### Organization History

- View all past organization sessions
- See session IDs, timestamps, and file counts
- Track what was organized and when

#### Selective Undo

- Choose specific sessions to undo
- Preview undo operations before applying
- Restore files to exact original locations

#### Keyboard Shortcuts

- `Ctrl+Enter`: Organize files
- `Ctrl+P`: Preview files
- `Ctrl+Z`: Undo last operation
- `Escape`: Close modals

## 🔧 Technical Details

### Architecture

```
┌─────────────────┐    HTTP API    ┌─────────────────┐    CLI Calls    ┌─────────────────┐
│   Web Browser   │ ────────────► │   Node.js       │ ─────────────► │ FileOrganizer   │
│  (Frontend UI)  │ ◄──────────── │   Server        │ ◄───────────── │ C++ Executable  │
└─────────────────┘               └─────────────────┘               └─────────────────┘
```

### Components

1. **Frontend (Browser)**:

   - `index.html`: Main interface structure
   - `styles.css`: Modern CSS styling with animations
   - `app.js`: JavaScript for user interactions and API calls

2. **Backend (Node.js)**:

   - `server.js`: HTTP server that bridges web interface to C++ executable
   - Handles API requests and spawns C++ processes
   - Serves static files and manages responses

3. **Integration**:
   - Web interface sends HTTP requests to Node.js server
   - Server translates requests to appropriate C++ command-line arguments
   - Results are formatted and sent back to the browser

### File Structure

```
web/
├── index.html          # Main web interface
├── styles.css          # CSS styling
├── app.js             # Frontend JavaScript
├── server.js          # Node.js backend server
├── start.bat          # Windows startup script
├── start.sh           # Linux/macOS startup script
└── README.md          # This file
```

## 🌐 API Endpoints

The Node.js server provides these internal API endpoints:

- `POST /api/preview` - Preview file organization
- `POST /api/organize` - Execute file organization
- `POST /api/history` - Get organization history
- `POST /api/undo` - Undo organization session

Each endpoint expects a JSON payload with `folderPath` and optional `sessionId`.

## 🎨 Customization

### Styling

The interface uses CSS custom properties (variables) for easy theming:

```css
:root {
  --primary-color: #4f46e5; /* Main accent color */
  --success-color: #10b981; /* Success operations */
  --warning-color: #f59e0b; /* Warning messages */
  --danger-color: #ef4444; /* Error states */
}
```

### Quick Folders

Edit the `setQuickFolder()` function in `app.js` to customize quick access folders for your system.

## 🔒 Security Notes

- **Local Only**: The server only accepts connections from localhost
- **No File System Access**: Web interface cannot directly access your file system
- **Process Isolation**: Each operation runs in a separate process
- **Safe Operations**: All file operations go through the tested C++ executable

## 🐛 Troubleshooting

### Common Issues

1. **"FileOrganizer.exe not found"**

   - Make sure you've built the C++ project first
   - Check that the executable exists in `../build/`

2. **"Port 3000 already in use"**

   - Another application is using port 3000
   - Close other applications or modify the port in `server.js`

3. **"Node.js not found"**

   - Install Node.js from https://nodejs.org/
   - Make sure it's added to your system PATH

4. **Browser doesn't open automatically**

   - Manually navigate to `http://localhost:3000`
   - Check firewall settings

5. **Operations time out**
   - Large folders may take time to process
   - The timeout is set to 60 seconds and can be adjusted in `server.js`

### Debug Mode

To enable debug output, modify `server.js` and add console logging:

```javascript
// Add after line with console.log
console.log("Debug: Args:", args);
console.log("Debug: Output:", stdout);
```

## 🚀 Future Enhancements

Possible improvements for future versions:

- **File System API**: Better folder browsing using modern browser APIs
- **Drag & Drop**: Drag folders directly onto the interface
- **Progress Streaming**: Real-time progress updates during organization
- **Custom Categories**: User-defined file organization rules
- **Batch Operations**: Organize multiple folders at once
- **Settings Panel**: Customize organization behavior
- **Dark Mode**: Toggle between light and dark themes

## 📝 License

This web interface is part of the FileOrganizer project and follows the same MIT License.

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes to the web interface
4. Test with the C++ executable
5. Submit a pull request

## 📞 Support

If you encounter issues:

1. Check this README for troubleshooting steps
2. Verify the C++ executable works from command line
3. Check the browser's developer console for JavaScript errors
4. Create an issue on the GitHub repository

---

**Happy Organizing! 📁✨**
