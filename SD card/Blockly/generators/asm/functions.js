/* this file contains the logic for converting the functions in the jump table to assembly code generators
*	Created by Arexx Engineering
*	Author: Johan Ras
*/

'use strict';

goog.provide('Blockly.asm.functions');

goog.require('Blockly.asm');

for(var func in jumpTable){
		
  Blockly.asm['functions_' + func] = function(block) {
    var functionName = block.type.replace("functions_",'');
    var parameters = jumpTable[functionName].parameterTypes;
	var codeGetParams = "";
	var codeAlignParams = "";
			
    var indent = Blockly.asm.indent;
			
    for(var i = parameters.length-1; i >= 0; i--)
    {
      var paramCode = Blockly.asm.valueToCode(block, "VAR_"+i, 0);
      if(paramCode == "")
      {
        paramCode = block.getFieldValue('VAR_'+i);
        if(paramCode == null)	
        {
          paramCode = "";
        }
        else
        {
          paramCode = indent + "ldi r24, " + (block.getFieldValue('VAR_'+i) || '0') + "\n";
        }
      }
					
      codeGetParams += paramCode;
      var typeLength = CppTypeSizes[typesCppToBlockly[parameters[i]]];
	
      if(typeLength == undefined && enums[parameters[i]] != null)
      {
        typeLength = 1;
      }
      
      if(i > 0)
      {
        if(typeLength == 1)
        {
          codeGetParams += indent + "push r24\n";
        }
        else if(typeLength == 2)
        {
          codeGetParams += indent + "push r24\n" +
          indent + "push r25\n";
        }
      }
    }
			
	var paramRegister = 24;
				
	for(var i = 0; i < parameters.length; i++)
	{
		var typeLength = CppTypeSizes[typesCppToBlockly[parameters[i]]];
	   console.log(typeLength);	
      
      
      if(typeLength == undefined && enums[parameters[i]] != null)
      {
        typeLength = 1;
      }
      
      if(typeLength == 1)
      {	
		if(i > 0)
        {
          codeAlignParams += indent + "pop r"+paramRegister+"\n";
        }
        paramRegister -= 2;
      }
      else if(typeLength == 2)
      {
        if(i > 0)
        {
          codeAlignParams += 	
            indent + "pop r"+(paramRegister+1)+"\n" +
            indent + "pop r"+(paramRegister)+"\n";
        }
        paramRegister -= 2;
      }
    }
				
    var code = codeGetParams + codeAlignParams + Blockly.asm.indent + "call " + functionName + "\n";
    if(jumpTable[functionName].returnType == "void")
      return code;
    else
      return  [code, Blockly.asm.ORDER_ATOMIC];				
  };
}