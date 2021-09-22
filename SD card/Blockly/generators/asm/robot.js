'use strict';

goog.provide('Blockly.asm.robot');

goog.require('Blockly.asm');


Blockly.asm['Robot_led'] = function(block) {
	var led = block.getFieldValue('led');
	var cmd = (block.getFieldValue('newValue') == '1') ? "sbi" : "cbi";

 	return Blockly.asm.indent + cmd + " PORTC, " + (led-1) + "\n";
};


Blockly.asm['arduino_pinmode'] = function(block) {
	var pin = parseInt(block.getFieldValue('pin'));
	var cmd = (block.getFieldValue('mode') == '1') ? "sbi" : "cbi";
	var pinInfo = pinNumberToPort(pin);
	
	console.log("block arduino_pinmode needs to be fixed");
	
 	return Blockly.asm.indent + cmd + " DDR" + pinInfo.port + ", " + pinInfo.pin + "\n";
};



Blockly.asm['arduino_setPin'] = function(block) {
	var pin = parseInt(block.getFieldValue('pin'));
	var boolCode = Blockly.asm.valueToCode(block, "VALUE");
	var pinInfo = pinNumberToPort(pin);
	
	var indent = Blockly.asm.indent;
	
	var lowLabel = Blockly.asm.getUniqueLabel();
	var endLabel = Blockly.asm.getUniqueLabel();
	
	console.log("block arduino_setPin needs to be fixed");
	
	var code = 	boolCode +
							indent + "tst r24\n" +
							indent + "breq " + lowLabel + "\n" +
							indent + "sbi PORT" + pinInfo.port + ", " + pinInfo.pin + "\n" +
							indent + "jmp " + endLabel + "\n" +
							lowLabel + ":\n" +
							indent + "cbi PORT" + pinInfo.port + ", " + pinInfo.pin + "\n" +
							endLabel + ":\n";
 	return code; 
};




function pinNumberToPort(number)
{
		var ret= {};
		
		if(number <= 5)
		{
			ret.port = 'F';
			ret.pin = number;
		}
		else if(number >= 6 && number <= 13)
		{
			ret.port = 'E';
			ret.pin = number - 6;
		}
		else 
		{
			ret.port = 'B';
			if(number == 14 || number == 15)
			{
				ret.pin = number - 10;
			}
			else if(number == 16)
			{
				ret.pin = 0;
			}
			else if(number == 17)
			{
				ret.pin = 2;
			}
			else if(number == 18)
			{
				ret.pin =	3;	
			}
			else if(number == 19)
			{
				ret.pin =	1;
			}
		}
		
		return ret;
}