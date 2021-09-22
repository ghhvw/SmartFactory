	"use strict";

var blocklyAddress =  0x4000/2
var ramAddress =      0x800
var tableAddress =    0x3F00/2;

var jumpTable = 
{
  "wait_ms":
    {
      returnType: "void",
      parameterTypes: ["int16_t"],
      text: "%{BKY_BL_WAIT_MS}",
      colour: "#4993AB",
      inline: true,
      category: "Time"
    },  
  "wait1sec":
    {
      returnType: "void",
      parameterTypes: [],
      text: "%{BKY_BL_WAIT_1_SEC}",
      colour: "#4993AB",
      inline: true,
      category: "Time"
    },
  //"moveToIdle":
  //  {
  //    returnType: "void",
  //    parameterTypes: [],
  //    text: "%{BKY_BL_MOVE_TO_IDLE}",
  //    colour: "#AB7D1E",
  //    inline: true,
  //    category: "Movement"
  //  },
  //"moveToUp":
  //  {
  //    returnType: "void",
  //    parameterTypes: [],
  //    text: "%{BKY_BL_MOVE_TO_UP}",
  //    colour: "#AB7D1E",
  //    inline: true,
  //    category: "Movement"
  //  },
  "PrintNums":
    {
      returnType: "void",
      parameterTypes: ["int16_t"],
      text: "%{BKY_BL_PRINT_NUMBER}",
      colour: "#000000",
      inline: true,
      category: "DEV"
    },
  "invert":
    {
      returnType: "int16_t",
      parameterTypes: ["int16_t"],
      text: "%{BKY_BL_INVERT}",
      colour: "%{BKY_MATH_HUE}",
      inline: true,
      category: "Math"
    },
  //"waitReached":
  //  {
  //    returnType: "void",
  //    parameterTypes: [],
  //    text: "%{BKY_BL_WAIT_REACHED}",
  //    colour: "#AB7D1E",
  //    inline: true,
  //    category: "Movement"
  //  },
  //"enableServos":
  //  {
  //    returnType: "void",
  //    parameterTypes: ["bool"],
  //    text: "%{BKY_BL_ENABLE_SERVOS}",
  //    colour: "#AB7D1E",
  //    inline: true,
  //    category: "Movement"
  //  },
  //"setJoint":
  //  {
  //    returnType: "void",
  //    parameterTypes: ["Joint","int16_t"],
  //    text: "%{BKY_BL_SET_JOINT}°",
  //    colour: "#AB7D1E",
  //    inline: true,
  //    category: "Movement"
  //  },
  //"moveSmooth":
  //  {
  //    returnType: "void",
  //    parameterTypes: ["int16_t","int16_t","int16_t","int16_t","int16_t","int16_t"],
  //    text: "%{BKY_BL_MOVE_SMOOTH}",
  //    colour: "#AB7D1E",
  //    inline: true,
  //    category: "Movement"
  //  },
  "add":
    {
      returnType: "int16_t",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_ADD}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "subtract":
    {
      returnType: "int16_t",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_SUBTRACT}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "multiply":
    {
      returnType: "int16_t",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_MULTIPLY}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "divide":
    {
      returnType: "int16_t",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_DIVIDE}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "equal":
    {
      returnType: "bool",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_EQUAL}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "bigger":
    {
      returnType: "bool",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_BIGGER}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "smaller":
    {
      returnType: "bool",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_SMALLER}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "biggerOrEqual":
    {
      returnType: "bool",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_BIGGER_OR_EQUAL}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "smallerOrEqual":
    {
      returnType: "bool",
      parameterTypes: ["int16_t","int16_t"],
      text: "%{BKY_BL_SMALLER_OR_EQUAL}",
      colour: "#a55b5b",
      inline: true,
      category: "Math"
    },
  "or":
    {
      returnType: "bool",
      parameterTypes: ["bool","bool"],
      text: "%{BKY_BL_OR}",
      colour: "#a55b5b",
      inline: true,
      category: "Logic"
    },
  "and":
    {
      returnType: "bool",
      parameterTypes: ["bool","bool"],
      text: "%{BKY_BL_AND}",
      colour: "#a55b5b",
      inline: true,
      category: "Logic"
    },
  "xor":
    {
      returnType: "bool",
      parameterTypes: ["bool","bool"],
      text: "%{BKY_BL_XOR}",
      colour: "#a55b5b",
      inline: true,
      category: "Logic"
    },
  "Reset":
  {
    returnType: "void",
    parameterTypes: [],
    text: "Reset",
    inline: true,
    category: "Logic"
  },
  "stepper":
  {
    returnType: "void",
    parameterTypes: ["int16_t","int16_t","Speed","ClockDirection"],
    text: "Stepper motor No.%1 steps %2, speed %3, direction %4",
    colour: "#AB7D1E",
    inline: true,
    category: "Movement"
  },
  "dc":
  {
    returnType: "void",
    parameterTypes: ["int16_t","Speed","ClockDirection"],
    text: "Conveyor motor No.%1, speed %2, direction %3",
    colour: "#AB7D1E",
    inline: true,
    category: "Movement"
  },
  "Solanoid":
  {
    returnType: "void",
    parameterTypes: ["int16_t", "inOut"],
    text: "Solanoid No.%1, %2",
    colour: "#AB7D1E",
    inline: true,
    category: "Movement"
  }
}


var categories = 
{
  "Logic":        {name: "%{BKY_CAT_LOGIC}",      colour: "#5b80a5"},
  "Loops":        {name: "%{BKY_CAT_LOOPS}",      colour: "#5ba55b"},
  "Time":         {name: "%{BKY_CAT_TIME}",       colour: "#4993AB"},
  "Math":         {name: "%{BKY_CAT_MATH}",       colour: "#5b5ba5"},
  "Movement":     {name: "%{BKY_CAT_MOVEMENT}",   colour: "#AB7D1E"},
  "IO":           {name: "%{BKY_CAT_IO}",         colour: "#a55b5b"},
}


var controllerRegisters = ".equ PORTB = 0x18\n" +
				          ".equ DDRB  = 0x17\n" +
						  ".equ PINB  = 0x16\n" +
						  ".equ PORTC = 0x15\n" +
						  ".equ DDRC  = 0x14\n" +
						  ".equ PINC  = 0x13\n";


var typesCppToBlockly = 
{
  int16_t: "Number",
  bool: "Boolean",
}

// put enums here. these will appear as dropdowns in blockly (these are 1-byte enums. the maximum value is 255)
var enums =
{
    "Joint":            [["shoulder rotation", '0'],["shoulder",'1'],["elbow", '2'],["wrist",'3'],["wrist rotation",'4'],["gripper",'5']],
    "Speed":            [["slow", '0'], ["normal",'1'], ["fast",'2']],
    "ClockDirection":   [["clockwise", '0'],["counterclockwise",'1']],
    "inOut":            [["in", '0'], ["out", '1']]
}

var CppTypeSizes = {
	Number: 2,	
	Boolean: 1,
	Joint: 1,
    Speed: 1,
    ClockDirection: 1,
    inOut: 1
}

function jumpTableToCode()
{
	var code = '';
	var i = 0;
	
	for(var func in jumpTable)
	{
		code += ".equ " + func + " = 0x" + wordToHexText(tableAddress+2*i) + "\n";	
		i++;
	}
	return code;
}
