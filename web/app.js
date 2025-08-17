// FileOrganizer Web Interface JavaScript

// Simple global functions for button handlers
function previewFiles() {
  const folderPath = getFolderPath();
  if (!folderPath) return;

  showProgress(true, 25, "Scanning files...");

  makeApiCall("preview", { folderPath })
    .then((result) => {
      showProgress(true, 100, "Preview complete!");
      setTimeout(() => showProgress(false), 1000);
      showResults("📋 File Preview", result.output);
      showNotification("Preview completed successfully", "success");
    })
    .catch((error) => {
      showProgress(false);
      showNotification("Failed to preview files", "error");
    });
}

function organizeFiles() {
  const folderPath = getFolderPath();
  if (!folderPath) return;

  if (
    !confirm(
      `Are you sure you want to organize files in:\n${folderPath}\n\nThis will move files into category folders.`
    )
  ) {
    return;
  }

  showProgress(true, 10, "Starting organization...");

  makeApiCall("organize", { folderPath })
    .then((result) => {
      showProgress(true, 100, "Organization complete!");
      setTimeout(() => showProgress(false), 1000);
      showResults("✅ Organization Complete", result.output);
      showNotification("Files organized successfully!", "success");
    })
    .catch((error) => {
      showProgress(false);
      showNotification("Failed to organize files", "error");
    });
}

function showHistory() {
  const folderPath = getFolderPath();
  if (!folderPath) return;

  updateStatus("Loading history...", "processing");

  makeApiCall("history", { folderPath })
    .then((result) => {
      document.getElementById("historyContent").innerHTML = `
        <pre style="white-space: pre-wrap; font-family: monospace; background: #f8f9fa; padding: 1rem; border-radius: 6px; border: 1px solid #e9ecef;">${result.output}</pre>
      `;
      document.getElementById("historyModal").style.display = "flex";
      updateStatus("History loaded", "success");
    })
    .catch((error) => {
      showNotification("Failed to load history", "error");
    });
}

function undoOrganization() {
  const folderPath = getFolderPath();
  if (!folderPath) return;

  updateStatus("Loading undo options...", "processing");

  makeApiCall("history", { folderPath })
    .then((result) => {
      const sessions = parseHistoryForSessions(result.output);

      if (sessions.length === 0) {
        showNotification("No organization history found", "warning");
        return;
      }

      showUndoModal(sessions);
    })
    .catch((error) => {
      showNotification("Failed to load undo options", "error");
    });
}

function setQuickFolder(folderType) {
  const folderInput = document.getElementById("folderPath");
  const os = detectOS();
  let folderPath = "";

  const username = "hp"; // Default username

  switch (os) {
    case "Windows":
      const basePath = `C:\\Users\\${username}`;
      switch (folderType) {
        case "Downloads":
          folderPath = `${basePath}\\Downloads`;
          break;
        case "Desktop":
          folderPath = `${basePath}\\Desktop`;
          break;
        case "Documents":
          folderPath = `${basePath}\\Documents`;
          break;
      }
      break;
    case "macOS":
      const macBasePath = `/Users/${username}`;
      switch (folderType) {
        case "Downloads":
          folderPath = `${macBasePath}/Downloads`;
          break;
        case "Desktop":
          folderPath = `${macBasePath}/Desktop`;
          break;
        case "Documents":
          folderPath = `${macBasePath}/Documents`;
          break;
      }
      break;
    default:
      const linuxBasePath = `/home/${username}`;
      switch (folderType) {
        case "Downloads":
          folderPath = `${linuxBasePath}/Downloads`;
          break;
        case "Desktop":
          folderPath = `${linuxBasePath}/Desktop`;
          break;
        case "Documents":
          folderPath = `${linuxBasePath}/Documents`;
          break;
      }
  }

  folderInput.value = folderPath;
  showNotification(`Set folder to ${folderType}`, "success");
}

function browseFolder() {
  showNotification(
    "Folder browser not available in web version. Please enter path manually.",
    "info"
  );
}

function clearResults() {
  document.getElementById("resultsSection").style.display = "none";
}

function closeModal() {
  document.getElementById("historyModal").style.display = "none";
}

function closeUndoModal() {
  document.getElementById("undoModal").style.display = "none";
  selectedSession = null;
}

function executeUndo() {
  const folderPath = getFolderPath();
  if (!folderPath || !selectedSession) {
    showNotification("Please select a session to undo", "warning");
    return;
  }

  if (
    !confirm(
      `Are you sure you want to undo organization session: ${selectedSession}?\n\nThis will restore files to their original locations.`
    )
  ) {
    return;
  }

  closeUndoModal();
  showProgress(true, 25, "Undoing organization...");

  makeApiCall("undo", { folderPath, sessionId: selectedSession })
    .then((result) => {
      showProgress(true, 100, "Undo complete!");
      setTimeout(() => showProgress(false), 1000);
      showResults("↩️ Undo Complete", result.output);
      showNotification("Organization undone successfully!", "success");
    })
    .catch((error) => {
      showProgress(false);
      showNotification("Failed to undo organization", "error");
    })
    .finally(() => {
      selectedSession = null;
    });
}

// Helper functions
let selectedSession = null;

function getFolderPath() {
  const folderPath = document.getElementById("folderPath").value.trim();
  if (!folderPath) {
    showNotification("Please enter a folder path", "error");
    return null;
  }
  return folderPath;
}

function detectOS() {
  const userAgent = navigator.userAgent;
  if (userAgent.indexOf("Win") !== -1) return "Windows";
  if (userAgent.indexOf("Mac") !== -1) return "macOS";
  if (userAgent.indexOf("Linux") !== -1) return "Linux";
  return "Unknown";
}

function updateStatus(message, type = "success") {
  const statusText = document.getElementById("statusText");
  const statusIndicator = document.getElementById("statusIndicator");

  if (statusText) statusText.textContent = message;

  const colors = {
    success: "#10b981",
    warning: "#f59e0b",
    error: "#ef4444",
    info: "#3b82f6",
    processing: "#6366f1",
  };

  if (statusIndicator) {
    statusIndicator.style.background = colors[type] || colors.success;
  }
}

function showProgress(show = true, percentage = 0, text = "Processing...") {
  const progressSection = document.getElementById("progressSection");
  const progressFill = document.getElementById("progressFill");
  const progressText = document.getElementById("progressText");

  if (show) {
    if (progressSection) progressSection.style.display = "block";
    if (progressFill) progressFill.style.width = percentage + "%";
    if (progressText) progressText.textContent = text;
    updateStatus(text, "processing");
  } else {
    if (progressSection) progressSection.style.display = "none";
  }
}

function showResults(title, content) {
  const resultsSection = document.getElementById("resultsSection");
  const resultsTitle = document.getElementById("resultsTitle");
  const resultsContent = document.getElementById("resultsContent");

  if (resultsTitle) resultsTitle.textContent = title;
  if (resultsContent) resultsContent.textContent = content;
  if (resultsSection) {
    resultsSection.style.display = "block";
    resultsSection.scrollIntoView({ behavior: "smooth" });
  }
}

function showNotification(message, type = "info") {
  const notification = document.createElement("div");
  notification.className = `notification notification-${type}`;
  notification.innerHTML = `
    <div class="notification-content">
      <span class="notification-icon">${getNotificationIcon(type)}</span>
      <span class="notification-message">${message}</span>
    </div>
  `;

  notification.style.cssText = `
    position: fixed;
    top: 20px;
    right: 20px;
    background: white;
    border-radius: 8px;
    box-shadow: 0 10px 25px rgba(0, 0, 0, 0.1);
    padding: 1rem 1.5rem;
    z-index: 1100;
    transform: translateX(400px);
    transition: transform 0.3s ease;
    border-left: 4px solid ${
      type === "error" ? "#ef4444" : type === "warning" ? "#f59e0b" : "#10b981"
    };
  `;

  document.body.appendChild(notification);

  setTimeout(() => {
    notification.style.transform = "translateX(0)";
  }, 100);

  setTimeout(() => {
    notification.style.transform = "translateX(400px)";
    setTimeout(() => {
      if (notification.parentNode) {
        notification.parentNode.removeChild(notification);
      }
    }, 300);
  }, 3000);
}

function getNotificationIcon(type) {
  const icons = {
    success: "✅",
    error: "❌",
    warning: "⚠️",
    info: "ℹ️",
  };
  return icons[type] || icons.info;
}

async function makeApiCall(endpoint, data = {}) {
  try {
    const response = await fetch(`/api/${endpoint}`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(data),
    });

    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }

    const result = await response.json();
    return result;
  } catch (error) {
    console.error(`API call to ${endpoint} failed:`, error);
    updateStatus("Error occurred", "error");
    throw error;
  }
}

function parseHistoryForSessions(historyOutput) {
  const sessions = [];
  const lines = historyOutput.split("\n");

  for (const line of lines) {
    if (line.includes("Session:")) {
      const match = line.match(
        /Session:\s*(\S+)\s*\((\d+)\s*files?\s*moved?\)/
      );
      if (match) {
        sessions.push({
          id: match[1],
          fileCount: match[2],
        });
      }
    }
  }

  return sessions.reverse(); // Most recent first
}

function showUndoModal(sessions) {
  const sessionsList = document.getElementById("sessionsList");
  if (!sessionsList) return;

  sessionsList.innerHTML = "";

  if (sessions.length === 0) {
    sessionsList.innerHTML = "<p>No organization sessions found.</p>";
  } else {
    sessions.forEach((session, index) => {
      const sessionDiv = document.createElement("div");
      sessionDiv.className = "session-item";
      sessionDiv.innerHTML = `
        <div class="session-id">${session.id}</div>
        <div class="session-details">${session.fileCount} files moved</div>
      `;

      sessionDiv.addEventListener("click", () => {
        document.querySelectorAll(".session-item").forEach((item) => {
          item.classList.remove("selected");
        });

        sessionDiv.classList.add("selected");
        selectedSession = session.id;
      });

      if (index === 0) {
        sessionDiv.classList.add("selected");
        selectedSession = session.id;
      }

      sessionsList.appendChild(sessionDiv);
    });
  }

  const undoModal = document.getElementById("undoModal");
  if (undoModal) undoModal.style.display = "flex";
}

// Initialize when DOM is loaded
document.addEventListener("DOMContentLoaded", function () {
  updateStatus("Ready");

  // Set default folder path
  const folderInput = document.getElementById("folderPath");
  if (folderInput && !folderInput.value) {
    const os = detectOS();
    if (os === "Windows") {
      folderInput.placeholder = "C:\\Users\\hp\\Downloads";
    } else if (os === "macOS") {
      folderInput.placeholder = "/Users/user/Downloads";
    } else {
      folderInput.placeholder = "/home/user/Downloads";
    }
  }

  // Setup keyboard shortcuts
  document.addEventListener("keydown", (e) => {
    if (e.ctrlKey || e.metaKey) {
      switch (e.key) {
        case "Enter":
          e.preventDefault();
          organizeFiles();
          break;
        case "p":
          e.preventDefault();
          previewFiles();
          break;
        case "z":
          e.preventDefault();
          undoOrganization();
          break;
      }
    }
    if (e.key === "Escape") {
      closeModal();
      closeUndoModal();
    }
  });

  // Setup modal click handlers
  const historyModal = document.getElementById("historyModal");
  if (historyModal) {
    historyModal.addEventListener("click", (e) => {
      if (e.target.id === "historyModal") {
        closeModal();
      }
    });
  }

  const undoModal = document.getElementById("undoModal");
  if (undoModal) {
    undoModal.addEventListener("click", (e) => {
      if (e.target.id === "undoModal") {
        closeUndoModal();
      }
    });
  }
});
