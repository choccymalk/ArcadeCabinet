//mame/mame nes -cart \'mame/roms/Super Mario Bros (E).nes\' -skip_gameinfo

// main.js
const { app, BrowserWindow, ipcMain } = require('electron/main');
const path = require('node:path');
const { spawn } = require('child_process');

// Configuration for your programs
const PROGRAMS = [
    { id: 'smb1', name: 'Super Mario Bros', path: 'mame/mame nes -cart mame/roms/smb1.nes -skip_gameinfo  ', icon: 'images/smb1.png' },
    { id: 'contra', name: 'Contra', path: 'mame/mame nes -cart mame/roms/contra.nes -skip_gameinfo  ', icon: 'images/contra.png' },
    { id: 'tetris', name: 'Tetris', path: 'mame/mame nes -cart mame/roms/tetris.nes -skip_gameinfo  ', icon: 'images/tetris.png' },
    { id: 'galaga', name: 'Galaga', path: 'mame/mame nes -cart mame/roms/galaga.nes -skip_gameinfo  ', icon: 'images/galaga.png' },
    { id: 'pacman', name: 'PacMan', path: 'mame/mame nes -cart mame/roms/pacman.nes -skip_gameinfo  ', icon: 'images/pacman.png' },
    { id: 'dk', name: 'Donkey Kong', path: 'mame/mame nes -cart mame/roms/dk.nes -skip_gameinfo  ', icon: 'images/dk.png' },
    { id: 'excitebike', name: 'Excitebike', path: 'mame/mame nes -cart mame/roms/excitebike.nes -skip_gameinfo  ', icon: 'images/excitebike.png' },
    { id: 'mkss', name: 'Mario Kart: Super Circuit', path: 'mame/mame gba -cart mame/roms/mkss.gba -skip_gameinfo  ', icon: 'images/mkss.jpg' },
];

const STARTUP_DELAY = 2000;

function createWindow() {
    const win = new BrowserWindow({
        fullscreen: 1,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            nodeIntegration: false,
            contextIsolation: true
        }
    });

    win.loadFile('index.html');
}

async function launchProgram(programPath) {
    return new Promise((resolve, reject) => {
        const process = spawn(programPath, [], {
            detached: true,
            stdio: 'ignore',
            shell: true
        });

        process.unref();

        process.on('error', (err) => {
            reject(err);
        });

        setTimeout(() => {
            if (process && !process.killed) {
                resolve();
            } else {
                reject(new Error('Program failed to start'));
            }
        }, STARTUP_DELAY);
    });
}

// Handle program launch request from renderer
ipcMain.handle('launch-program', async (_, programId) => {
    try {
        const program = PROGRAMS.find(p => p.id === programId);
        if (!program) {
            throw new Error('Program not found');
        }

        await launchProgram(program.path);
        // On Windows, uncomment to switch focus:
        // const { exec } = require('child_process');
        // exec(`powershell -command "(New-Object -ComObject WScript.Shell).AppActivate('${program.name}')"`)
        
        app.quit();
        return { success: true };
    } catch (error) {
        return { success: false, error: error.message };
    }
});

// Send program data to renderer
ipcMain.handle('get-programs', () => PROGRAMS);

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});