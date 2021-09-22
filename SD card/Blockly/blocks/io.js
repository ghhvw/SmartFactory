'use strict';

goog.provide('Blockly.Blocks.io');  // Deprecated
goog.provide('Blockly.Constants.io');

goog.require('Blockly.Blocks');




Blockly.Blocks['io_button'] = {
category: "IO",
init: function(){        
        this.jsonInit({
						"type": "input_button",
						"message0": "%{BKY_BL_BUTTON}",
						"args0": [
							{
								"type": "field_dropdown",
								"name": "BUTTON",
								"options": [
									["1", "1"],
									["2", "2"]
								]
							}
						],
						"output": "Boolean",
						"colour": categories[this.category].colour,
						"tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
						"helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}"
				});
   }
}



Blockly.Blocks['io_setBit'] = {
init: function(){
    
        this.jsonInit({
                "type": "io_delay",
                "message0": "set bit %1 of register %2 to %3",
								"args0": [
									{
										"type": "field_dropdown",
										"name": "bit",
										"options": [
											["0", "0"],
											["1", "1"],
											["2", "2"],
											["3", "3"],
											["4", "4"],
											["5", "5"],
											["6", "6"],
											["7", "7"],
										]
									},
									{
										"type": "field_dropdown",
										"name": "register",
										"options": [
											["PORTB", "PORTB"],
											["DDRB", "DDRB"]
										]
									},
									{
										"type": "field_dropdown",
										"name": "newValue",
										"options": [
											["0", "0"],
											["1", "1"]
										]
									},
								],
		  
							"previousStatement": null,
            	"nextStatement": null,
              "colour": "#000000",
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
       	});
    }
}



Blockly.Blocks['io_led'] = {
category: "IO",
init: function(){
    
        this.jsonInit({
                "type": "Robot_led",
                "message0": "%{BKY_BL_LED}",
								"args0": [
									{
										"type": "field_dropdown",
										"name": "led",
										"options": [
											["1", "1"],
											["2", "2"],
											["3", "3"],
											["4", "4"],
										]
									},
									{
										"type": "field_dropdown",
										"name": "newValue",
										"options": [
											["%{BKY_TXT_OFF}", "0"],
											["%{BKY_TXT_ON}", "1"]
										]
									},
								],
		
              "category": "IO",
              "previousStatement": null,
              "nextStatement": null,
              "colour": categories[this.category].colour,
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
       	});
    }
}



// WIP
Blockly.Blocks['io_pinmode'] = {
category: "DEV",
init: function(){
    
        this.jsonInit({
                "type": "arduino_pinmode",
                "message0": "set %1 as %2",
								"args0": [
									{
										"type": "field_dropdown",
										"name": "pin",
										"options": [
											["A0", 0],
											["A1", 1],
											["A2", 2],
											["A3", 3],
											["A4", 4],
											["A5", 5],
											["D0", 6],
											["D1", 7],
											["D2", 8],
											["D3", 9],
											["D4", 10],
											["D5", 11],
											["D6", 12],
											["D7", 13],
											["D8", 14],
											["D9", 15],
											["D10", 16],
											["D11", 17],
											["D12", 18],
											["D13", 19],
										]
									},
									{
										"type": "field_dropdown",
										"name": "newValue",
										"options": [
											["input", "0"],
											["output", "1"]
										]
									},
								],
								
              "previousStatement": null,
              "nextStatement": null,
              "colour": categories[this.category].colour,
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
       	});
    }
}


// WIP
Blockly.Blocks['io_setPin'] = {
category: "DEV",
init: function(){
    
        this.jsonInit({
                "type": "arduino_pinmode",
                "message0": "set %1 to %2",
								"args0": [
									{
										"type": "field_dropdown",
										"name": "pin",
										"options": [
											["A0", 0],
											["A1", 1],
											["A2", 2],
											["A3", 3],
											["A4", 4],
											["A5", 5],
											["D0", 6],
											["D1", 7],
											["D2", 8],
											["D3", 9],
											["D4", 10],
											["D5", 11],
											["D6", 12],
											["D7", 13],
											["D8", 14],
											["D9", 15],
											["D10", 16],
											["D11", 17],
											["D12", 18],
											["D13", 19],
										]
									},
									{
										"type": "input_value",
										"name": "VALUE",
										"check": "Boolean"
									}
								],
								
							"previousStatement": null,
            	"nextStatement": null,
              "colour": categories[this.category].colour,
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
       	});
    }
}