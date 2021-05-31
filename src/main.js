const { SSL_OP_EPHEMERAL_RSA } = require('constants');
const electron = require('electron');
const path = require('path');
//const remote = require('remote'); // Load remote compnent that contains the dialog dependency
//const dialog = remote.require('dialog'); // Load the dialogs component of the OS
const fs = require('fs'); // Load the File System to execute our common tasks (CRUD)
const resFilePath = path.join(__dirname, '../Analyses/listeContamination.txt');

const analyse = require('idsips');

const { app, BrowserWindow, Menu, ipcMain } = electron;
// SET ENV
process.env.NODE_ENV = 'production';

let mainWindow;
let fileWindow;

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', function() {
    mainWindow = new BrowserWindow({
        width: 620,
        height: 500,
        //trun nodeIntegration to true
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            enableRemoteModule: true,
        }
    });

    // and load the index.html of the app.
    mainWindow.loadFile(path.join(__dirname, 'index.html'));

    // Open the DevTools.
    //mainWindow.webContents.openDevTools();

    // Close all windows when main window is closed
    mainWindow.on('close', function() {
        app.quit();
    })

    //----------------Build menu from template-------------------//
    const mainMenu = Menu.buildFromTemplate(mainMenuTemplate)
        //Insert menu
    Menu.setApplicationMenu(mainMenu);
    //----------------------------------------------------------// 

});

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) { // eslint-disable-line global-require
    app.quit();
}




// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('activate', () => {
    // On OS X it's common to re-create a window in the app when the
    // dock icon is clicked and there are no other windows open.
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow();
    }
});

//--------------------------Create menu template-------------------//
const mainMenuTemplate = [{
    label: 'File',
    submenu: [

        {
            label: 'Quit',
            accelerator: process.platform == 'darwin' ? 'Command+Q' : 'Ctrl+Q',
            click() {
                app.quit();
            }
        }
    ]
}];


//-----------------------------INDEX.html------------------------------//
//----------------------- BUTTON 1 Analyse Tout------------------------//

ipcMain.on("btnScanAllClick", function(event, arg) {
    //create analyseWindow 
    var analyseWindow = new BrowserWindow({
        width: 620,
        height: 500,
        show: false,
        //trun nodeIntegration to true
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            enableRemoteModule: true,
        }

    }); // end of create a new window

    analyseWindow.loadFile(path.join(__dirname, 'analyseWindow.html'));
    analyseWindow.show();
    console.log('arg: ', arg);
    arg = analyse.firstAnalysis();
    // call analysis_treatment()
    if (arg >= 1) {
        const content = fs.readFileSync(resFilePath, 'utf8').toString().split(/\r?\n/);
        console.log('content= ' + content);
        const lineBreak = '                                                                ';
        arg = arg + lineBreak + " Les fichiers infectés :           " + lineBreak + content;
        console.log('arg= ' + arg);
    }


    analyseWindow.webContents.on('did-finish-load', () => {
        analyseWindow.webContents.send("btnScanAllClick", arg);

    });

});


//----------------------- BUTTON 2 ------------------------//

ipcMain.on("btnScan1Click", function(event, arg) {
    //create new window
    fileWindow = new BrowserWindow({
        width: 620,
        height: 500,
        show: false,
        //trun nodeIntegration to true
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            enableRemoteModule: true,
        }

    }); // end of create a new window

    fileWindow.loadFile(path.join(__dirname, 'fileWindow.html'));
    fileWindow.show();
    fileWindow.on('close', function() {
        fileWindow = null;
    })
});


ipcMain.on("item:add", function(event, item) {
    //create new window
    var analyseWindow = new BrowserWindow({
        width: 620,
        height: 500,
        show: false,
        //trun nodeIntegration to true
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            enableRemoteModule: true,
        }

    }); // end of create a new window

    analyseWindow.loadFile(path.join(__dirname, 'analyseWindow.html'));
    analyseWindow.show();
    console.log('from main.js, before calling folderAnalysis, item: ', item);
    item = analyse.folderAnalysis(item);

    analyseWindow.webContents.on('did-finish-load', () => {
        analyseWindow.webContents.send("btnScanAllClick", item);
        console.log("from mains js, item is : " + item);

    });
    fileWindow.close();

});


//----------------------- BUTTON 3 Github Web ------------------------//
/*
//----------------------- BUTTON 3 ------------------------//
>>>>>>> e607fce38f437c888e6cbc6a3388e70b4de521aa
ipcMain.on("btnclick", function(event, arg) {
    //create new window
    var newWindow = new BrowserWindow({
        width: 620,
        height: 500,
        show: false,
        webPreferences: {
            webSecurity: false,
            plugins: true,
            nodeIntegration: false
        }
    }); // create a new window

    var github = "https://github.com/zhoulin-yu/ids-ips"; // loading an external url. We can load our own another html file, like how we load index.html earlier

    newWindow.loadURL(github);
    newWindow.show();

    // inform the render process that the assigned task finished. Show a message in html
    // event.sender.send in ipcMain will return the reply to renderprocess
    event.sender.send("btnclick-task-finished", "yes");
});
*/

//--------------------------AnalyseWIndow---------------------------------------//
//-------------------BUTTON 1 OF analyseWIndow---------------------------//
ipcMain.on("quarantineClick", function(event, arg) {
    analyse.allQuarantine();
    console.log("lance quanrantine");
});

//-------------------BUTTON 2 OF analyseWIndow---------------------------//
ipcMain.on("blockClick", function(event, arg) {
    analyse.allBlock();
    console.log("lance allBlock");
});

//-------------------BUTTON 3 OF analyseWIndow---------------------------//
ipcMain.on("donothingClick", function(event, arg) {
    analyse.removeAnalyseAndListeContamine();
    console.log("lance removeAnalyseAndListeContamine");
});


//-------------------Read File---------------------------------//




//If mac, add empty object to menu

if (process.platform == 'darwin') {
    mainMenuTemplate.unshift({ label: '' });
}
if (process.env.NODE_ENV !== 'production') {
    mainMenuTemplate.push({
        label: 'Developper Tools',
        submenu: [{
                label: 'Toggle DevTools',
                accelerator: process.platform == 'darwin' ? 'Command+I' : 'Ctrl+I',
                click(item, focuseWindow) {
                    focuseWindow.toggleDevTools();
                }
            },
            {
                role: 'reload'
            }
        ]
    })
}
//-----------------------------------------------------------------//