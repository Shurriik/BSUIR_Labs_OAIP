@echo off
chcp 65001 >nul
title BJCH Программа
echo Запуск BJCH программы...

:: Проверяем Python (если используем .py файл)
:: Если используем .exe - убрать эту проверку

:: Запускаем программу
if exist "main.exe" (
    echo Запуск main.exe...
    start "" "main.exe"
) else if exist "main.py" (
    echo Запуск main.py через Python...
    python main.py
) else (
    echo Ошибка: Не найден файл main.exe или main.py!
    echo Убедитесь, что программа установлена правильно.
    pause
)