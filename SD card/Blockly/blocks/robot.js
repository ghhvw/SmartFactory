'use strict';

goog.provide('Blockly.Blocks.Robot');  // Deprecated
goog.provide('Blockly.Constants.Robot');

goog.require('Blockly.Blocks');


Blockly.Blocks['Robot_led'] = {
init: function(){
    
        this.jsonInit({
                "type": "Robot_led",
                "message0": "turn LED %1 %2",
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
											["off", "0"],
											["on", "1"]
										]
									},
								],
								
		      "category": "IO",
              "previousStatement": null,
              "nextStatement": null,
              "colour": "%{BKY_LOGIC_HUE}",
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
       	});
    }
}




Blockly.Blocks['arduino_pinmode'] = {
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
								
		      "category": "DEV",
              "previousStatement": null,
              "nextStatement": null,
              "colour": "#3861AB",
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
       	});
    }
}



Blockly.Blocks['arduino_setPin'] = {
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
				
              "category": "DEV",
		      "previousStatement": null,
              "nextStatement": null,
              "colour": "#3861AB",
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
       	});
    }
}
