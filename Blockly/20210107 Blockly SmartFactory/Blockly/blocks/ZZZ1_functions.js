/* this file contains the logic for converting the functions in the jump table to blocks
*	Created by Arexx Engineering
*	Author: Johan Ras
*/

'use strict';

goog.provide('Blockly.Blocks.functions');  // Deprecated
goog.provide('Blockly.Constants.functions');

goog.require('Blockly.Blocks');



var getCategoryColour = function(cat)
{
  var colour = "#000000";
  if(categories[cat].colour != undefined)
  {
    colour = categories[cat].colour;
  }
  
  return colour;
}



for(var func in jumpTable)
{
	var name = func;  
    var func = jumpTable[func];
    var var_args = [];
    var retType = typesCppToBlockly[func.returnType];
    var isEnumType = false;
	
    for(var j = 0; j < jumpTable[name].parameterTypes.length; j++)
    {
      var paramType = func.parameterTypes[j];
      
      if(enums[paramType] != null)
      {
        isEnumType = true;
            var_args.push({
			type: "field_dropdown", 
			options: enums[paramType], 
			name: "VAR_"+j});
      }
      else
      {
	     var_args.push({
		    type:  "input_value", 
			name: "VAR_"+j, 
			check: typesCppToBlockly[func.parameterTypes[j]] });
      }
      
      /*for(var currentEnum in enums)
      {
       
        if(func.parameterTypes[j] == currentEnum)
        {
		    isEnumType = true;
            var_args.push({
				type: "field_dropdown", 
				options: enums[currentEnum], 
				name: "VAR_"+j});
		}
      }
      
      if(isEnumType == false)
      {
	     var_args.push({
		    type:  "input_value", 
			name: "VAR_"+j, 
			check: typesCppToBlockly[func.parameterTypes[j]] });
      }*/
	}

    
    if(func.returnType == "void")
    {
        Blockly.Blocks['functions_' + name] = {
        functionName: name,
        args: var_args,
		inline: func.inline,
        category: func.category,
          
        init: function(){
            this.jsonInit({
                    "type": "functions_" + this.functionName,
                    "message0": jumpTable[this.functionName].text,
                    "args0": this.args,
                    "colour": getCategoryColour(this.category),
                    "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
                    "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
                    "previousStatement": null,
                    "nextStatement": null,
				    "inputsInline":	this.inline
                });
            }
        }   
    }
    else
    {
        Blockly.Blocks['functions_' + name] = {
        functionName: name,
        args: var_args,
        ret: retType,
		inline: func.inline,
        category: func.category,
          
          init: function(){
            this.jsonInit({
                    "type": "functions_" + this.functionName,
                    "message0": jumpTable[this.functionName].text,
                    "args0": this.args,
                    "output": this.ret,
                    "colour": getCategoryColour(this.category),
                    "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
                    "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
                    "inputsInline":	this.inline
                });
            }
        }   
    }
    
    
    
    
}