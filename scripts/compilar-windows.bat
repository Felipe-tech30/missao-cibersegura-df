@echo off
setlocal

cd /d "%~dp0.."

set "RAYLIB=C:\raylib"
set "GCC=%RAYLIB%\w64devkit\bin\gcc.exe"

if not exist "%GCC%" (
    echo Nao foi possivel encontrar o compilador em %GCC%
    echo Ajuste a variavel RAYLIB neste arquivo para a sua instalacao.
    exit /b 1
)

"%GCC%" -std=c99 -Wall -Wextra -Wpedantic ^
  -I"include" -I"%RAYLIB%\raylib\src" ^
  src\main.c src\jogo.c src\mapa.c src\personagem.c src\ameacas.c ^
  src\dicas.c src\interface.c src\salvamento.c ^
  -L"%RAYLIB%\w64devkit\lib" -lraylib -lopengl32 -lgdi32 -lwinmm ^
  -o pcdf_missao_cibersegura.exe

if errorlevel 1 exit /b 1
echo Compilacao concluida: pcdf_missao_cibersegura.exe
