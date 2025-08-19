const http = require("http");
const fs = require("fs");
const path = require("path");
const { spawn } = require("child_process");
const url = require("url");

class FileOrganizerServer {
    constructor() {
        this.port = 3000;
        this.executablePath = path.join(
            __dirname,
            "..",
            "build",
            "FileOrganizer.exe"
        );
        this.webDir = __dirname;

        // Check if executable exists
        if (!fs.existsSync(this.executablePath)) {
            console.error(
                "FileOrganizer.exe not found at:",
                this.executablePath
            );
            console.log("Please build the project first using build.bat");
            process.exit(1);
        }
    }

    start() {
        const server = http.createServer((req, res) => {
            this.handleRequest(req, res);
        });

        server.listen(this.port, () => {
            console.log("🚀 FileOrganizer Web Interface Started!");
            console.log("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
            console.log(`🌐 Web Interface: http://localhost:${this.port}`);
            console.log(`🔧 C++ Executable: ${this.executablePath}`);
            console.log("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
            console.log("💡 Quick Start:");
            console.log("   1. Open http://localhost:3000 in your browser");
            console.log("   2. Enter a folder path to organize");
            console.log("   3. Use Preview to see what will be organized");
            console.log("   4. Use Organize to apply changes");
            console.log("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");

            // Try to open browser automatically
            this.openBrowser();
        });

        server.on("error", (err) => {
            if (err.code === "EADDRINUSE") {
                console.error(`❌ Port ${this.port} is already in use.`);
                console.log(
                    "💡 Try closing other applications or use a different port."
                );
            } else {
                console.error("❌ Server error:", err);
            }
        });
    }

    openBrowser() {
        const { exec } = require("child_process");
        const url = `http://localhost:${this.port}`;

        // Detect OS and open browser
        const platform = process.platform;
        let command;

        switch (platform) {
            case "win32":
                command = `start ${url}`;
                break;
            case "darwin":
                command = `open ${url}`;
                break;
            default:
                command = `xdg-open ${url}`;
        }

        exec(command, (error) => {
            if (error) {
                console.log(
                    `⚠️  Could not auto-open browser. Please visit: ${url}`
                );
            }
        });
    }

    handleRequest(req, res) {
        const parsedUrl = url.parse(req.url, true);
        const pathname = parsedUrl.pathname;

        // Enable CORS
        res.setHeader("Access-Control-Allow-Origin", "*");
        res.setHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.setHeader("Access-Control-Allow-Headers", "Content-Type");

        if (req.method === "OPTIONS") {
            res.writeHead(200);
            res.end();
            return;
        }

        // Serve static files
        if (pathname === "/" || pathname === "/index.html") {
            this.serveFile(res, "index.html", "text/html");
        } else if (pathname === "/debug" || pathname === "/debug.html") {
            this.serveFile(res, "debug.html", "text/html");
        } else if (pathname === "/styles.css") {
            this.serveFile(res, "styles.css", "text/css");
        } else if (pathname === "/app.js") {
            this.serveFile(res, "app.js", "application/javascript");
        } else if (pathname.startsWith("/api/")) {
            this.handleApiRequest(req, res, pathname);
        } else {
            this.send404(res);
        }
    }

    serveFile(res, filename, contentType) {
        const filePath = path.join(this.webDir, filename);

        fs.readFile(filePath, (err, data) => {
            if (err) {
                this.send404(res);
                return;
            }

            res.writeHead(200, { "Content-Type": contentType });
            res.end(data);
        });
    }

    handleApiRequest(req, res, pathname) {
        if (req.method !== "POST") {
            this.sendJson(res, { error: "Method not allowed" }, 405);
            return;
        }

        let body = "";
        req.on("data", (chunk) => {
            body += chunk.toString();
        });

        req.on("end", () => {
            try {
                const data = JSON.parse(body);
                this.processApiRequest(res, pathname, data);
            } catch (error) {
                console.error("JSON parse error:", error);
                this.sendJson(res, { error: "Invalid JSON" }, 400);
            }
        });
    }

    async processApiRequest(res, pathname, data) {
        const endpoint = pathname.replace("/api/", "");
        const { folderPath, sessionId } = data;

        if (!folderPath) {
            this.sendJson(res, { error: "Folder path is required" }, 400);
            return;
        }

        console.log(`� Web Interface: http://localhost:${this.port}`);

        try {
            let args = [];

            switch (endpoint) {
                case "preview":
                    args = ["--list", folderPath];
                    break;
                case "organize":
                    args = ["--organize", folderPath];
                    break;
                case "history":
                    args = ["--history", folderPath];
                    break;
                case "undo":
                    args = sessionId
                        ? ["--undo", folderPath, sessionId]
                        : ["--undo", folderPath];
                    break;
                default:
                    this.sendJson(res, { error: "Unknown endpoint" }, 400);
                    return;
            }

            const result = await this.runFileOrganizer(args);
            this.sendJson(res, { success: true, output: result.output });
        } catch (error) {
            console.error(`❌ API Error: ${endpoint}`, error.message);
            this.sendJson(
                res,
                {
                    success: false,
                    error: error.message,
                    output: error.output || "",
                },
                500
            );
        }
    }

    runFileOrganizer(args) {
        return new Promise((resolve, reject) => {
            const process = spawn(this.executablePath, args, {
                cwd: path.dirname(this.executablePath),
                stdio: ["pipe", "pipe", "pipe"],
            });

            let stdout = "";
            let stderr = "";

            process.stdout.on("data", (data) => {
                stdout += data.toString();
            });

            process.stderr.on("data", (data) => {
                stderr += data.toString();
            });

            process.on("close", (code) => {
                if (code === 0) {
                    resolve({
                        output: stdout || "Operation completed successfully",
                        code: code,
                    });
                } else {
                    reject({
                        message: `Process exited with code ${code}`,
                        output: stderr || stdout || "Unknown error occurred",
                        code: code,
                    });
                }
            });

            process.on("error", (error) => {
                reject({
                    message: `Failed to start process: ${error.message}`,
                    output: "",
                    code: -1,
                });
            });

            // Set a timeout for long-running operations
            setTimeout(() => {
                if (!process.killed) {
                    process.kill();
                    reject({
                        message: "Operation timed out",
                        output: "The operation took too long to complete",
                        code: -1,
                    });
                }
            }, 60000); // 60 second timeout
        });
    }

    sendJson(res, data, statusCode = 200) {
        res.writeHead(statusCode, { "Content-Type": "application/json" });
        res.end(JSON.stringify(data));
    }

    send404(res) {
        res.writeHead(404, { "Content-Type": "text/plain" });
        res.end("404 Not Found");
    }
}

// Handle graceful shutdown
process.on("SIGINT", () => {
    console.log("\n🛑 Shutting down FileOrganizer Web Interface...");
    console.log("👋 Goodbye!");
    process.exit(0);
});

process.on("SIGTERM", () => {
    console.log("\n🛑 Shutting down FileOrganizer Web Interface...");
    console.log("👋 Goodbye!");
    process.exit(0);
});

// Start the server
const server = new FileOrganizerServer();
server.start();
