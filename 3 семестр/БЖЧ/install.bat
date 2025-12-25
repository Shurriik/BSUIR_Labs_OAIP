@echo off
chcp 65001 >nul
echo ============================================
echo      УСТАНОВЩИК BJCH ПРОГРАММЫ
echo ============================================
echo.
echo Этот установщик скопирует программу на ваш компьютер
echo и создаст ярлык на рабочем столе.
echo.
echo Нажмите любую клавишу для начала установки...
pause >nul
echo.

:: Создаем папку программы
set "PROGRAM_FOLDER=%USERPROFILE%\Documents\BJCH_Program"
echo Создаем папку программы...
if not exist "%PROGRAM_FOLDER%" mkdir "%PROGRAM_FOLDER%"

:: Копируем ВСЕ файлы из текущей папки
echo Копируем файлы программы...
xcopy /E /Y /I * "%PROGRAM_FOLDER%" >nul

:: Создаем ярлык на рабочем столе
echo Создаем ярлык на рабочем столе...
echo Set oWS = WScript.CreateObject("WScript.Shell") > "%TEMP%\shortcut.vbs"
echo sLinkFile = "%USERPROFILE%\Desktop\BJCH Программа.lnk" >> "%TEMP%\shortcut.vbs"
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> "%TEMP%\shortcut.vbs"
echo oLink.TargetPath = "%PROGRAM_FOLDER%\run.bat" >> "%TEMP%\shortcut.vbs"
echo oLink.WorkingDirectory = "%PROGRAM_FOLDER%" >> "%TEMP%\shortcut.vbs"
echo oLink.Save >> "%TEMP%\shortcut.vbs"
cscript //nologo "%TEMP%\shortcut.vbs" >nul
del "%TEMP%\shortcut.vbs" >nul

:: Создаем ярлык в меню Пуск
echo Создаем ярлык в меню Пуск...
if not exist "%APPDATA%\Microsoft\Windows\Start Menu\Programs\BJCH" (
    mkdir "%APPDATA%\Microsoft\Windows\Start Menu\Programs\BJCH"
)
echo Set oWS = WScript.CreateObject("WScript.Shell") > "%TEMP%\shortcut2.vbs"
echo sLinkFile = "%APPDATA%\Microsoft\Windows\Start Menu\Programs\BJCH\BJCH Программа.lnk" >> "%TEMP%\shortcut2.vbs"
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> "%TEMP%\shortcut2.vbs"
echo oLink.TargetPath = "%PROGRAM_FOLDER%\run.bat" >> "%TEMP%\shortcut2.vbs"
echo oLink.WorkingDirectory = "%PROGRAM_FOLDER%" >> "%TEMP%\shortcut2.vbs"
echo oLink.Save >> "%TEMP%\shortcut2.vbs"
cscript //nologo "%TEMP%\shortcut2.vbs" >nul
del "%TEMP%\shortcut2.vbs" >nul

echo.
echo ============================================
echo      УСТАНОВКА ЗАВЕРШЕНА!
echo ============================================
echo.
echo Программа установлена в: %PROGRAM_FOLDER%
echo.
echo На рабочем столе создан ярлык "BJCH Программа"
echo В меню Пуск: Пуск -> Программы -> BJCH
echo.
echo Нажмите:
echo [1] - Запустить программу сейчас
echo [2] - Открыть папку с программой
echo [3] - Выйти
echo.
choice /c 123 /n /m "Выберите действие: "

if errorlevel 3 goto exit
if errorlevel 2 goto open_folder
if errorlevel 1 goto run_program

:run_program
echo Запускаем программу...
cd /d "%PROGRAM_FOLDER%"
start "" "run.bat"
goto exit

:open_folder
echo Открываю папку с программой...
explorer "%PROGRAM_FOLDER%"
goto exit

:exit
echo.
echo Нажмите любую клавишу для выхода...
pause >nul
exit