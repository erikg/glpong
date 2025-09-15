@echo off
echo Installing GLPong...

REM Create installation directory
if not exist "C:\Program Files\GLPong" (
    mkdir "C:\Program Files\GLPong"
)

REM Copy files (this would be replaced with actual extraction commands)
echo Copying game files...
xcopy /s /e /i "bin\*" "C:\Program Files\GLPong\"

REM Create desktop shortcut
echo Creating desktop shortcut...
powershell -Command "& {$WshShell = New-Object -comObject WScript.Shell; $Shortcut = $WshShell.CreateShortcut('$env:USERPROFILE\Desktop\GLPong.lnk'); $Shortcut.TargetPath = 'C:\Program Files\GLPong\glpong.exe'; $Shortcut.WorkingDirectory = 'C:\Program Files\GLPong'; $Shortcut.Save()}"

REM Create start menu shortcut
echo Creating start menu shortcut...
if not exist "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\GLPong" (
    mkdir "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\GLPong"
)
powershell -Command "& {$WshShell = New-Object -comObject WScript.Shell; $Shortcut = $WshShell.CreateShortcut('C:\ProgramData\Microsoft\Windows\Start Menu\Programs\GLPong\GLPong.lnk'); $Shortcut.TargetPath = 'C:\Program Files\GLPong\glpong.exe'; $Shortcut.WorkingDirectory = 'C:\Program Files\GLPong'; $Shortcut.Save()}"

echo GLPong installation completed!
echo You can now run GLPong from the Desktop or Start Menu.
pause