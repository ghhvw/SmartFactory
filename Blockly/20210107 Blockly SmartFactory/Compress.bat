@echo off
title Arexx hERB compressor

echo f | xcopy /v /y "%~dp0\assembler\AVRasm_Compressed.js" "%~dp0compressed\assembler\AVRasm.js"

echo D | xcopy /s /e /v /y "%~dp0\Blockly\msg\js" "%~dp0compressed\Blockly\msg\js"
echo f | xcopy /v /y "%~dp0\Blockly\asm_compressed.js" "%~dp0compressed\Blockly\asm.js"
echo f | xcopy /v /y "%~dp0\Blockly\blockly_compressed.js" "%~dp0compressed\Blockly\blockly.js"
echo f | xcopy /v /y "%~dp0\Blockly\blocks_compressed.js" "%~dp0compressed\Blockly\blocks.js"

echo D | xcopy /s/e /v /y "%~dp0\bootstrap-4.0.0-dist" "%~dp0compressed\bootstrap-4.0.0-dist"
echo D | xcopy /s/e /v /y "%~dp0\images" "%~dp0compressed\images"
echo D | xcopy /s/e /v /y "%~dp0\jquery" "%~dp0compressed\jquery"
echo D | xcopy /s/e /v /y "%~dp0\js" "%~dp0compressed\js"
echo D | xcopy /s/e /v /y "%~dp0\Languages" "%~dp0compressed\Languages"

echo f | xcopy /v /y "%~dp0index.html" "%~dp0compressed\index.html"
echo f | xcopy /v /y "%~dp0jmpTbl.js" "%~dp0compressed\jmpTbl.js"
echo f | xcopy /v /y "%~dp0style.css" "%~dp0compressed\style.css"

powershell -Command "(gc '%~dp0compressed\index.html') -replace 'Blockly/blockly_compressed.js', 'Blockly/blockly.js' -replace 'blockly/asm_compressed.js', 'blockly/asm.js' -replace 'blockly/blocks_compressed.js', 'blockly/blocks.js' | Out-File '%~dp0compressed\index.html' -encoding ASCII"

pause
