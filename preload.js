// preload.js
const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('electronAPI', {
    launchProgram: (programId) => ipcRenderer.invoke('launch-program', programId),
    getPrograms: () => ipcRenderer.invoke('get-programs')
});