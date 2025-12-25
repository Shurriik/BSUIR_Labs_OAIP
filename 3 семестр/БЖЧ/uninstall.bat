@echo off
chcp 65001 >nul
echo ============================================
echo      УДАЛЕНИЕ BJCH ПРОГРАММЫ
echo ============================================
echo.
echo ВНИМАНИЕ: Это удалит программу с вашего компьютера!
echo.
set /p confirm="Вы уверены? (да/нет): "
if /i not "%confirm%"=="да" (
    echo Удаление отменено.
    pause
    exit
)

echo Удаляем программу...
set "PROGRAM_FOLDER=%USERPROFILE%\Documents\BJCH_Program"

:: Удаляем папку программы
if exist "%PROGRAM_FOLDER%" (
    rmdir /S /Q "%PROGRAM_FOLDER%"
    echo ✓ Папка программы удалена
)

:: Удаляем ярлык с рабочего стола
if exist "%USERPROFILE%\Desktop\BJCH Программа.lnk" (
    del "%USERPROFILE%\Desktop\BJCH Программа.lnk"
    echo ✓ Ярлык с рабочего стола удален
)

:: Удаляем ярлык из меню Пуск
if exist "%APPDATA%\Microsoft\Windows\Start Menu\Programs\BJCH" (
    rmdir /S /Q "%APPDATA%\Microsoft\Windows\Start Menu\Programs\BJCH"
    echo ✓ Ярлык из меню Пуск удален
)

echo.
echo ============================================
echo      ПРОГРАММА УДАЛЕНА!
echo ============================================
echo.
pause