///home/username/mame/mame nes -cart \'/home/username/mame/roms/Super Mario Bros (E).nes\' -skip_gameinfo

// main.js
const { app, BrowserWindow, ipcMain } = require('electron/main');
const path = require('node:path');
const { spawn } = require('child_process');

// Configuration for your programs
const PROGRAMS = [
    { id: 'smb1', name: 'Super Mario Bros', path: '/home/username/mame/mame nes -cart /home/username/mame/roms/smb1.nes -skip_gameinfo  ', icon: 'images/smb1.png' },
    { id: 'contra', name: 'Contra', path: '/home/username/mame/mame nes -cart /home/username/mame/roms/contra.nes -skip_gameinfo  ', icon: 'images/smb1.png' },
    { id: 'tetris', name: 'Tetris', path: '/home/username/mame/mame nes -cart /home/username/mame/roms/tetris.nes -skip_gameinfo  ', icon: 'images/smb1.png' },
    { id: 'castlevania', name: 'Castlevania', path: '/home/username/mame/mame nes -cart /home/username/mame/roms/castlevania.nes -skip_gameinfo  ', icon: 'images/smb1.png' },
    { id: 'pacman', name: 'PacMan', path: '/home/username/mame/mame nes -cart /home/username/mame/roms/pacman.nes -skip_gameinfo  ', icon: 'images/smb1.png' },
    { id: 'dk', name: 'Donkey Kong', path: '/home/username/mame/mame nes -cart /home/username/mame/roms/dk.nes -skip_gameinfo  ', icon: 'images/smb1.png' }
];

const STARTUP_DELAY = 2000;

function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
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