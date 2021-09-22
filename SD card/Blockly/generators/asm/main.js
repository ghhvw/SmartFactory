goog.provide('Blockly.asm.main');

goog.require('Blockly.asm');



Blockly.asm.listVars = function()
{
    var vars = workspace.getAllVariables();
    console.log(vars);
}


Blockly.asm['main_start'] = function(block) {
	return Blockly.asm.statementToCode(block, 'DO');
};

Blockly.asm['main_loop'] = function(block) {
	return Blockly.asm.statementToCode(block, 'DO');
};