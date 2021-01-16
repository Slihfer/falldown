[Setup]
AppName=Ground
AppVersion=1.0
DefaultDirName={autopf64}/Ground
DefaultGroupName=Ground

[Files]
Source: "out\build\x64-Release\src\Ground.exe"; DestDir: "{app}"
Source: "assets\graphics\sprites\*"; DestDir: "{app}/assets/graphics/sprites/"
Source: "assets\audio\music\*"; DestDir: "{app}/assets/audio/m/"
Source: "assets\audio\sfx\*"; DestDir: "{app}/assets/audio/sfx/"

[Tasks]
Name: startmenu; Description: "Create a startmenu shortcut"; Flags: unchecked
Name: desktopicon; Description: "Create a desktop icon"; Flags: unchecked

[Icons]
Name: "{group}\Ground"; Filename: "{app}/Ground.exe"; IconFilename: "{app}/assets/sprites/icon.ico"; Tasks: startmenu
Name: "{commondesktop}\Ground"; Filename: "{app}/Ground.exe"; IconFilename: "{app}/assets/sprites/icon.ico"; Tasks: desktopicon