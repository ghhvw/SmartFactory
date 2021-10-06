"use strict";

var blocklyAddress = 0x8000 / 2
var ramAddress = 0x800
var tableAddress = 0x7E00 / 2;

//plaats text in taalbestanden in "Languages" map voor vertaallingen
//volgorde van deze blocklys moet hetzelfde zijn als de jump_table in main.cpp
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
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_ADD}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "subtract":
  {
    returnType: "int16_t",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_SUBTRACT}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "multiply":
  {
    returnType: "int16_t",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_MULTIPLY}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "divide":
  {
    returnType: "int16_t",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_DIVIDE}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "equal":
  {
    returnType: "bool",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_EQUAL}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "bigger":
  {
    returnType: "bool",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_BIGGER}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "smaller":
  {
    returnType: "bool",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_SMALLER}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "biggerOrEqual":
  {
    returnType: "bool",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_BIGGER_OR_EQUAL}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "smallerOrEqual":
  {
    returnType: "bool",
    parameterTypes: ["int16_t", "int16_t"],
    text: "%{BKY_BL_SMALLER_OR_EQUAL}",
    colour: "#a55b5b",
    inline: true,
    category: "Math"
  },
  "or":
  {
    returnType: "bool",
    parameterTypes: ["bool", "bool"],
    text: "%{BKY_BL_OR}",
    colour: "#a55b5b",
    inline: true,
    category: "Logic"
  },
  "and":
  {
    returnType: "bool",
    parameterTypes: ["bool", "bool"],
    text: "%{BKY_BL_AND}",
    colour: "#a55b5b",
    inline: true,
    category: "Logic"
  },
  "xor":
  {
    returnType: "bool",
    parameterTypes: ["bool", "bool"],
    text: "%{BKY_BL_XOR}",
    colour: "#a55b5b",
    inline: true,
    category: "Logic"
  },
  //  "Reset":
  //  {
  //    returnType: "void",
  //    parameterTypes: [],
  //    text: "Reset",
  //    inline: true,
  //    category: "Logic"
  //  },
  //  "stepper":
  //  {
  //    returnType: "void",
  //    parameterTypes: ["int16_t","int16_t","Speed","ClockDirection"],
  //    text: "Stepper motor No.%1 steps %2, speed %3, direction %4",
  //   colour: "#AB7D1E",
  //   inline: true,
  //    category: "Movement"
  //  },
  //  "dc":
  //  {
  //    returnType: "void",
  //    parameterTypes: ["int16_t","Speed","ClockDirection"],
  //    text: "Conveyor motor No.%1, speed %2, direction %3",
  //    colour: "#AB7D1E",
  //    inline: true,
  //    category: "Movement"
  //  },
  "ToggleLED":
  {
    returnType: "void",
    parameterTypes: [],
    text: "%{BKY_BL_TOGGLELED}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  },
  "LED":
  {
    returnType: "void",
    parameterTypes: ["onOff"],
    text: "%{BKY_BL_SETLED}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  },
  "DigitalRead":
  {
    returnType: "bool",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_DIGITALREAD}",
    colour: "#4993AB",
    inline: true,
    category: "IO",
  },
  "MoveBelt":
  {
    returnType: "void",
    parameterTypes: ["leftRight", "int16_t", "int16_t"],
    text: "%{BKY_BL_MOVEBELT}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "StopBelt":
  {
    returnType: "void",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_STOPBELT}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "MoveSorterArmTo":
  {
    returnType: "void",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_MOVESORTERARMTO}",
    colour: "#4993AB",
    inline: true,
    category: "Movement",
  },
  "MoveSorterArmDistance":
  {
    returnType: "void",
    parameterTypes: ["leftRight", "int16_t"],
    text: "%{BKY_BL_MOVESORTERARMDISTANCE}",
    colour: "#4993AB",
    inline: true,
    category: "Movement",
  },
  "SorterArmIsFinished":
  {
    returnType: "bool",
    parameterTypes: [],
    text: "%{BKY_BL_SORTERARMISFINISHED}",
    colour: "#4993AB",
    inline: true,
    category: "Movement",
  },
  "StopSorterArm":
  {
    returnType: "void",
    parameterTypes: [],
    text: "%{BKY_BL_STOPSORTERARM}",
    colour: "#4993AB",
    inline: true,
    category: "Movement",
  },
  "HomeSorterArm":
  {
    returnType: "void",
    parameterTypes: [],
    text: "%{BKY_BL_HOMESORTERARM}",
    colour: "#4993AB",
    inline: true,
    category: "Movement",
  },
  "MoveTurntable":
  {
    returnType: "void",
    parameterTypes: ["ClockDirection", "int16_t", "int16_t"],
    text: "%{BKY_BL_MOVETURNTABLE}",
    colour: "#4993ab",
    inline: true,
    category: "Movement"
  },
  "StopTurntable":
  {
    returnType: "void",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_STOPTURNTABLE}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "DemoTestBlock":
  {
    returnType: "void",
    parameterTypes: [],
    text: "%{BKY_BL_DEMOTESTBLOCK}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "StopDemoTestBlock":
  {
    returnType: "void",
    parameterTypes: [],
    text: "%{BKY_BL_STOPDEMOTESTBLOCK}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "SetAddres":
  {
    returnType: "void",
    parameterTypes: ["int8_t", "int8_t"],
    text: "%{BKY_BL_SETADDRES}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "MoveElevator":
  {
    returnType: "void",
    parameterTypes: ["upDown"],
    text: "%{BKY_BL_MOVEELEVATOR}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "StopElevator":
  {
    returnType: "void",
    parameterTypes: [],
    text: "%{BKY_BL_STOPELEVATOR}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "ElevatorIsReady":
  {
    returnType: "bool",
    parameterTypes: [],
    text: "%{BKY_BL_ELEVATORISREADY}",
    colour: "#4993AB",
    inline: true,
    category: "Movement"
  },
  "Solenoid":
  {
    returnType: "void",
    parameterTypes: ["int16_t", "inOut"],
    text: "%{BKY_BL_SOLENOID}",
    colour: "#AB7D1E",
    inline: true,
    category: "Movement"
  },
  "PulseSolenoid":
  {
    returnType: "void",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_PULSESOLENOID}",
    colour: "#AB7D1E",
    inline: true,
    category: "Movement"
  },
  "AnalogRead":
  {
    returnType: "int16_t",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_ANALOGREAD}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  },
  "ReadSharpSensor":
  {
    returnType: "int16_t",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_READSHARPSENSOR}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  },
  "OptocouplerRead":
  {
    returnType: "bool",
    parameterTypes: ["int16_t"],
    text: "%{BKY_BL_OPTOCOUPLERREAD}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  },
  "ReadColourSensor":
  {
    //	  returnType: "colour",
    returnType: "int16_t",
    parameterTypes: [],
    text: "%{BKY_BL_READCOLOURSENSOR}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  },
  /*	"CompareColours":
      {
      returnType: "bool",
        parameterTypes: ["colour", "colour"],
        text: "%{BKY_BL_COMPARECOLOURS}",
        colour: "#4993AB",
        inline: true,
        category: "Math"
      }*/
  "SelectColour":
  {
    returnType: "int16_t",
    parameterTypes: ["Colours"],
    text: "%{BKY_BL_SELECTCOLOUR}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  },
  "SetRelay":
  {
    returnType: "void",
    parameterTypes: ["int16_t","int16_t"],
    text: "%{BKY_BL_SETRELAY}",
    colour: "#4993AB",
    inline: true,
    category: "IO"
  }
}

var categories =
{
  "Logic": { name: "%{BKY_CAT_LOGIC}", colour: "#1a4bfd" },
  "Loops": { name: "%{BKY_CAT_LOOPS}", colour: "#11d011" },
  "Time": { name: "%{BKY_CAT_TIME}", colour: "#31cffa" },
  "Math": { name: "%{BKY_CAT_MATH}", colour: "#9e00ff" },
  "Movement": { name: "%{BKY_CAT_MOVEMENT}", colour: "#ffac00" },
  "IO": { name: "%{BKY_CAT_IO}", colour: "#c10e0e" },
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
  "Joint": [["shoulder rotation", '0'], ["shoulder", '1'], ["elbow", '2'], ["wrist", '3'], ["wrist rotation", '4'], ["gripper", '5']],
  "Speed": [["slow", '0'], ["normal", '1'], ["fast", '2']],
  "ClockDirection": [["↻", '0'], ["↺", '1']],
  "inOut": [["in", '0'], ["out", '1']],
  "onOff": [["off", '0'], ["on", '1']],
  "upDown": [["Down", '0'], ["Upp", '1']], // [["🡣", '0'], ["🡡", '1']], // Woorden en pijlen zijn bijde mogelijk, pijlen worden mogelijk alleen niet door alle browsers ondersteund
  "leftRight": [["🡠", '1'], ["🡢", '0']],
  "Colours": [[{ 'src': 'images/black.png', 'width': 20, 'height': 15 }, '0'],
  [{ 'src': 'images/blue.png', 'width': 20, 'height': 15 }, '1'],
  [{ 'src': 'images/green.png', 'width': 20, 'height': 15 }, '2'],
  [{ 'src': 'images/cyan.png', 'width': 20, 'height': 15 }, '3'],
  [{ 'src': 'images/red.png', 'width': 20, 'height': 15 }, '4'],
  [{ 'src': 'images/magenta.png', 'width': 20, 'height': 15 }, '5'],
  [{ 'src': 'images/yellow.png', 'width': 20, 'height': 15 }, '6'],
  [{ 'src': 'images/white.png', 'width': 20, 'height': 15 }, '7']],
}

var CppTypeSizes = {
  Number: 2,
  Boolean: 1,
  Joint: 1,
  Speed: 1,
  ClockDirection: 1,
  inOut: 1,
  //	Colour: 7
}

function jumpTableToCode() {
  var code = '';
  var i = 0;

  for (var func in jumpTable) {
    code += ".equ " + func + " = 0x" + wordToHexText(tableAddress + 2 * i) + "\n";
    i++;
  }
  return code;
}
