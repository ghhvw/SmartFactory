"use strict";

var Languages = {};
Languages.BlockNames = {};
Languages.HelpTexts = {};

// categories
Blockly.Msg.CAT_LOGIC                     = "Logic";
Blockly.Msg.CAT_LOOPS                     = "Loops";
Blockly.Msg.CAT_TIME                      = "Time";
Blockly.Msg.CAT_MATH                      = "Math";
Blockly.Msg.CAT_MOVEMENT                  = "Movement";
Blockly.Msg.CAT_IO                        = "IO";
Blockly.Msg.CAT_VARIABLES                 = "Variables";

// variables
Blockly.Msg.VAR_BOOL                      = "Boolean";
Blockly.Msg.VAR_NUMBER                    = "Number";
Blockly.Msg.VAR_COLOUR                    = "Colour";

// hardcoded blocks text
Blockly.Msg.BL_IF_ELSE_IF                 = "if";
Blockly.Msg.BL_IF_ELSE_THEN               = "do";
Blockly.Msg.BL_IF_ELSE_ELSE               = "else do";
Blockly.Msg.BL_NEGATE                     = "not %1";
Blockly.Msg.BL_LED                        = "turn LED %1 %2";
Blockly.Msg.BL_BUTTON                     = "button %1 is pressed";
Blockly.Msg.BL_WHILE					  = "while %1 do %2";
Blockly.Msg.BL_REPEAT_TIMES				  = "for %1 times";
Blockly.Msg.BL_REPEAT_DO				  = "do";
Blockly.Msg.BL_REPEAT_FOREVER			  = "repeat forever";

// jumptable blocks
Blockly.Msg.BL_WAIT_MS                    = "wait for %1 milliseconds";
Blockly.Msg.BL_WAIT_1_SEC                 = "wait for 1 second";
Blockly.Msg.BL_MOVE_TO_IDLE               = "go to idle position";
Blockly.Msg.BL_MOVE_TO_UP                 = "go to up position";
Blockly.Msg.BL_PRINT_NUMBER               = "print number %1";
Blockly.Msg.BL_INVERT                     = "-%1";
Blockly.Msg.BL_WAIT_REACHED               = "wait until target is reached";
Blockly.Msg.BL_ENABLE_SERVOS              = "turn on servo %1";
Blockly.Msg.BL_SET_JOINT                  = "move %1 to %2";
Blockly.Msg.BL_MOVE_SMOOTH                = "go to %1° %2° %3° %4° %5° %6°";
Blockly.Msg.BL_ADD                        = "%1 + %2";
Blockly.Msg.BL_SUBTRACT                   = "%1 - %2";
Blockly.Msg.BL_MULTIPLY                   = "%1 * %2";
Blockly.Msg.BL_DIVIDE                     = "%1 / %2";
Blockly.Msg.BL_EQUAL                      = "%1 == %2";
Blockly.Msg.BL_BIGGER                     = "%1 > %2";
Blockly.Msg.BL_SMALLER                    = "%1 < %2";
Blockly.Msg.BL_BIGGER_OR_EQUAL            = "%1 >= %2";
Blockly.Msg.BL_SMALLER_OR_EQUAL           = "%1 <= %2";
Blockly.Msg.BL_OR                         = "%1 or %2";
Blockly.Msg.BL_AND                        = "%1 and %2";
Blockly.Msg.BL_XOR                        = "one of %1 or %2";
Blockly.Msg.BL_TOGGLELED                  = "toggle LED";
Blockly.Msg.BL_SETLED                     = "LED %1";
Blockly.Msg.BL_DIGITALREAD                = "digital read %1";
Blockly.Msg.BL_MOVEBELT                   = "move belt %2 %1 with speed %3";
Blockly.Msg.BL_STOPBELT                   = "stop belt %1";
Blockly.Msg.BL_MOVESORTERARMTO            = "move sorter arm to postion: %1";
Blockly.Msg.BL_MOVESORTERARMDISTANCE      = "move sorter arm %1 with %2 steps";
Blockly.Msg.BL_SORTERARMISFINISHED        = "sorter arm is finished";
Blockly.Msg.BL_STOPSORTERARM              = "stop sorter arm";
Blockly.Msg.BL_HOMESORTERARM              = "homing squence of sorterarm";
Blockly.Msg.BL_MOVETURNTABLE              = "turn turntable %2 %1 with speed %3";
Blockly.Msg.BL_STOPTURNTABLE              = "stop turntable %1";
Blockly.Msg.BL_DEMOTESTBLOCK              = "Demo Test Block"; // Test code
Blockly.Msg.BL_STOPDEMOTESTBLOCK          = "Stop Demo Test Block"; // Test code
Blockly.Msg.BL_SETADDRES                  = "Set Addres of stepperdriver from %1 to %2"; // Stel adres stepperdriver in
Blockly.Msg.BL_MOVEELEVATOR               = "move elevator %1";
Blockly.Msg.BL_STOPELEVATOR               = "stop elevator";
Blockly.Msg.BL_ELEVATORISREADY            = "elevator is ready";
Blockly.Msg.BL_SOLENOID                   = "solenoid no.%1 %2";
Blockly.Msg.BL_PULSESOLENOID              = "solenoid no.%1 pulse";
Blockly.Msg.BL_ANALOGREAD                 = "analog read %1";
Blockly.Msg.BL_READSHARPSENSOR            = "sharp sensor %1";
Blockly.Msg.BL_OPTOCOUPLERREAD            = "read optocoupler %1";
Blockly.Msg.BL_SELECTCOLOUR               = "%1";
Blockly.Msg.BL_READCOLOURSENSOR           = "colour sensor";
Blockly.Msg.BL_COMPARECOLOURS             = "colour %1 == colour %2";
Blockly.Msg.BL_SETRELAY                   = "Set relay %2 to %1";

// hardcoded blocks help
//logic
Languages.BlockNames["controls_simple_if"]          = "if-do";
Languages.BlockNames["controls_ifelse"]             = "if-do-else do";
Languages.BlockNames["Logic_boolean"]               = "true/false : boolean";
Languages.BlockNames["logic_negate"]                = "not : logic inverter";
Languages.BlockNames["functions_or"]                = "or";
Languages.BlockNames["functions_and"]               = "and";
Languages.BlockNames["functions_xor"]               = "one of-or : xor";
//loops
Languages.BlockNames["controls_repeat_ext"]         = "for-times-do";
Languages.BlockNames["controls_while"]              = "while-do";
Languages.BlockNames["controls_repeat_forever"]     = "repeat forever";
//time
Languages.BlockNames["functions_wait_ms"]           = "wait for n milliseconds";
Languages.BlockNames["functions_wait1sec"]          = "wait for 1 second";
//math
Languages.BlockNames["math_number"]                 = "0 : number";
Languages.BlockNames["functions_invert"]            = "- : invert";
Languages.BlockNames["functions_add"]               = "+ : add";
Languages.BlockNames["functions_subtract"]          = "- : subtract";
Languages.BlockNames["functions_multiply"]          = "* : multiply";
Languages.BlockNames["functions_divide"]            = "/ : divide";
Languages.BlockNames["functions_equal"]             = "== : equal";
Languages.BlockNames["functions_bigger"]            = "> : bigger";
Languages.BlockNames["functions_smaller"]           = "< : smaller";
Languages.BlockNames["functions_biggerOrEqual"]     = ">= : bigger or equal";
Languages.BlockNames["functions_smallerOrEqual"]    = "<= : smaller or equal";
Languages.BlockNames["functions_CompareColours"]    = "colour-== colour-";
//movement
Languages.BlockNames["functions_MoveBelt"]			= "move belt";
Languages.BlockNames["functions_StopBelt"]			= "stop belt";
Languages.BlockNames["functions_MoveSorterArmTo"]	= "move sorter arm to postion";
Languages.BlockNames["functions_MoveSorterArmDistance"] = "move sorter arm left or right with distance of x steps";
Languages.BlockNames["functions_SorterArmIsFinished"]	= "sorter arm is finished";
Languages.BlockNames["functions_StopSorterArm"]	    = "stop sorter arm";
Languages.BlockNames["functions_HomeSorterArm"]     = "homing sequence of sorter arm";
Languages.BlockNames["functions_MoveTurntable"]		= "turn turntable, Round like a Record";
Languages.BlockNames["functions_StopTurntable"]		= "stop turntable";
Languages.BlockNames["functions_DemoTestBlock"]     = "Demo Test Block"; // Test code
Languages.BlockNames["functions_StopDemoTestBlock"] = "Stop Demo Test Block"; // Test code
Languages.BlockNames["functions_SetAddres"]         = "Set Addres"; // Stel adres van stepperdriver in
Languages.BlockNames["functions_MoveElevator"]		= "move elevator";
Languages.BlockNames["functions_StopElevator"]		= "stop elevator";
Languages.BlockNames["functions_ElevatorReady"]		= "elevator is ready";
Languages.BlockNames["functions_BeweegLift"]        = "beweeg lift"; // Nieuwe lift code
Languages.BlockNames["functions_StopLifft"]         = "stop lift"; // Nieuwe lift code
Languages.BlockNames["functions_LiftIsKlaar"]       = "de lift is klaar"; // Nieuwe lift code
Languages.BlockNames["functions_Solenoid"]			= "solenoid no.-";
Languages.BlockNames["functions_PulseSolenoid"]		= "solenoid no.-pulse";
//io
Languages.BlockNames["functions_SelectColour"]      = "colour";
Languages.BlockNames["io_button"]                   = "button-is pressed";
Languages.BlockNames["io_led"]                      = "turn LED-on/off";
Languages.BlockNames["functions_ToggleLED"]			= "toggle LED";
Languages.BlockNames["functions_LED"]               = "LED on/off";
Languages.BlockNames["functions_DigitalRead"]		= "digital read";
Languages.BlockNames["functions_AnalogRead"]		= "analog read";
Languages.BlockNames["functions_ReadSharpSensor"]   = "sharp sensor";
Languages.BlockNames["functions_OptocouplerRead"]   = "read optocoupler";
Languages.BlockNames["functions_ReadColourSensor"]  = "colour sensor";
//variables
Languages.BlockNames["variables_create_number"]     = "create number";
Languages.BlockNames["variables_get_number"]        = "get number";
Languages.BlockNames["variables_set_number"]        = "set number to";
Languages.BlockNames["variables_create_Boolean"]    = "create boolean";
Languages.BlockNames["variables_get_Boolean"]       = "get boolean";
Languages.BlockNames["variables_set_Boolean"]       = "set boolean to";
Languages.BlockNames["variables_create_Colour"]     = "create colour";
Languages.BlockNames["variables_get_Colour"]        = "get colour";
Languages.BlockNames["variables_set_Colour"]        = "set colour to";
//overig/ongebruikt \/
Languages.BlockNames["functions_moveToIdle"]        = "move to up";
Languages.BlockNames["functions_moveToUp"]          = "ga naar rechtop positie";
Languages.BlockNames["functions_PrintNums"]         = "print number";
Languages.BlockNames["functions_waitReached"]       = "wacht tot positie is bereikt";
Languages.BlockNames["functions_enableServos"]      = "servo's aanzetten";
Languages.BlockNames["functions_setJoint"]          = "set joint";
Languages.BlockNames["functions_moveSmooth"]        = "move smooth";

// hardcoded blocks help description
//logic
Languages.HelpTexts["controls_simple_if"]           = "Voer iets uit als de parameter waar is.";
Languages.HelpTexts["controls_ifelse"]              = "Is de parameter waar? Voer de eerste code uit. Zo niet, voer de tweede code uit.";
Languages.HelpTexts["Logic_boolean"]                = "Voer de waarde \"waar\" of \"onwaar\" in.";
Languages.HelpTexts["logic_negate"]                 = "Maakt van true --> false en van false --> true.";
Languages.HelpTexts["functions_or"]                 = "Hier komt \"waar\" uit wanneer één van de waarden van beide parameters waar is.";
Languages.HelpTexts["functions_and"]                = "Hier komt \"waar\" uit wanneer de waarden van beide parameters waar zijn.";
Languages.HelpTexts["functions_xor"]                = "Hier komt \"waar\" uit wanneer één van de waarden van de parameters waar is (en de andere waarde onwaar).";
//loops
Languages.HelpTexts["controls_repeat_ext"]          = "Voer de code een aantal keer uit, aangegeven door de parameter.";
Languages.HelpTexts["controls_while"]               = "Voer de code uit totdat de parameter onwaar is.";
Languages.HelpTexts["controls_repeat_forever"]      = "Eindeloze lus. Blijf voor altijd deze code uitvoeren.";
//time
Languages.HelpTexts["functions_wait_ms"]            = "Wacht voor een aantal milliseconden. Er zitten 1000 milliseconden in 1 seconde.";
Languages.HelpTexts["functions_wait1sec"]           = "Wacht voor 1 seconde.";
//math
Languages.HelpTexts["math_number"]                  = "Geef een nummer mee als parameter. Werkt goed met een \"" + Languages.BlockNames["controls_repeat_ext"] + "\".";
Languages.HelpTexts["functions_invert"]             = "Maak van een positief getal een negatief getal en andersom.";
Languages.HelpTexts["functions_add"]                = "Tel de getallen bij elkaar op.";
Languages.HelpTexts["functions_subtract"]           = "Trek de getallen van elkaar af.";
Languages.HelpTexts["functions_multiply"]           = "Vermenigvuldig de getallen.";
Languages.HelpTexts["functions_divide"]             = "Deel de getallen.";
Languages.HelpTexts["functions_equal"]              = "Vergelijk de parameters met elkaar. Wanneer ze gelijk zijn komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_bigger"]             = "Als de waarde van de eerste parameter groter is dan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_smaller"]            = "Als de waarde van de eerste parameter kleiner is dan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_biggerOrEqual"]      = "Als de waarde van de eerste parameter groter of gelijk is aan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_smallerOrEqual"]     = "Als de waarde van de eerste parameter kleiner of gelijk is aan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_CompareColours"]     = "Als beide kleuren hetzelfde zijn komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
//movement
Languages.HelpTexts["functions_MoveBelt"]			= "Beweeg de band naar links of naar rechts.";
Languages.HelpTexts["functions_StopBelt"]			= "Stop de band.";
Languages.HelpTexts["functions_MoveSorterArmTo"]    = "Move sorter arm to postion.";
Languages.HelpTexts["functions_MoveSorterArmDistance"] = "Move sorter arm left or right with a number of steps .";
Languages.HelpTexts["functions_SorterIsFinished"]   = "Sorter arm is finished.";
Languages.HelpTexts["functions_StopSorterArm"]      = "Stop sorter arm.";
Languages.HelpTexts["functions_HomeSorterArm"]      = "Homing sequence of sorter arm";
Languages.HelpTexts["functions_MoveTurntable"]		= "Beweeg de draaischijf linksom of rechtsom.";
Languages.HelpTexts["functions_StopTurntable"]		= "Stop de draaischijf.";
Languages.HelpTexts["functions_DemoTestBlock"]      = "Demo Test Block, motor #8 moet gaan draaien.";
Languages.HelpTexts["functions_StopDemoTestBlock"]  = "Stop Demo Test Block, motor#8 moet stoppen met draaien.";
Languages.HelpTexts["functions_SetAddres"]          = "Stel adres in van stepperdriver."; // Adres
Languages.HelpTexts["functions_MoveElevator"]		= "Beweeg de lift, hij stopt automatisch. Gebruik blok \"" + Languages.BlockNames["functions_ElevatorReady"] + "\" om te checken of de lift klaar is.";
Languages.HelpTexts["functions_StopElevator"]		= "Stop de lift.";
Languages.HelpTexts["functions_ElevatorIsReady"]	= "Geeft \"waar\" terug wanneer de lift klaar is met bewegen.";
Languages.HelpTexts["functions_Solenoid"]			= "Zet een solenoïde aan of uit. Zorg ervoor dat de solenoïde niet aan blijft staan, want dan wordt deze warm.";
Languages.HelpTexts["functions_PulseSolenoid"]		= "Zet een solenoïde kort aan.";
//io
Languages.HelpTexts["functions_SelectColour"]       = "Gebruik dit blok om sensorwaarden te vergelijken met een kleur.";
Languages.HelpTexts["io_button"]                    = "Lees een button uit. Werkt goed met een \"" + Languages.BlockNames["controls_simple_if"] + "\".";
Languages.HelpTexts["io_led"]                       = "Schakel een LED-lampje aan of uit.";
Languages.HelpTexts["functions_ToggleLED"]          = "Zet een LED-lampje aan als deze uit was, of uit als deze aan was.";
Languages.HelpTexts["functions_LED"]                = "Schakel een LED-lampje aan of uit.";
Languages.HelpTexts["functions_DigitalRead"]		= "Lees een digitale poort uit, bijvoorbeeld een van een schakelaar. Hier komt \"waar\" of \"onwaar\" uit. De poorten gaan van 1 t/m 12.";
Languages.HelpTexts["functions_AnalogRead"]			= "Lees een analoge poort uit, bijvoorbeeld die van de sharp sensor. Geeft een waarde terug van 0 t/m 255. De poorten gaan van 1 t/m 5.";
Languages.HelpTexts["functions_ReadSharpSensor"]	= "Lees de sharp sensor uit. Geeft een waarde terug in centimeters (4cm t/m 30cm). De sharp sensor is niet heel precies. De poorten hebben dezelfde range als blok \"" + Languages.BlockNames["functions_AnalogRead"] + "\".";
Languages.HelpTexts["functions_OptocouplerRead"]	= "Lees een optocoupler uit. Een optocoupler wordt gebruikt om een galvanische scheiding tussen circuits aan te brengen. Dit betekent dat er minder storing bij het lezen optreedt. De poorten gaan van 0 t/m 5.";
Languages.HelpTexts["functions_ReadColourSensor"]   = "Lees een kleursensor uit. Geeft een kleurwaarde terug.";
//variables
Languages.HelpTexts["variables_create_number"]      = "Maak een nummer-variabele. Stel deze in met blok \"" + Languages.BlockNames["variables_set_number"] + "\" en lees hem uit met blok \"" + Languages.BlockNames["variables_get_number"] + "\". Deze variabele kan ook een kleur opslaan.";
Languages.HelpTexts["variables_get_number"]         = "Lees een nummer-variabele uit.";
Languages.HelpTexts["variables_set_number"]         = "Stel een nummer-variabele in.";
Languages.HelpTexts["variables_create_Boolean"]     = "Maak een boolean-variabele. Stel deze in met blok \"" + Languages.BlockNames["variables_set_Boolean"] + "\" en lees hem uit met blok \"" + Languages.BlockNames["variables_get_Boolean"] + "\".";
Languages.HelpTexts["variables_get_Boolean"]        = "Lees een boolean-variabele uit.";
Languages.HelpTexts["variables_set_Boolean"]        = "Stel een boolean-variabele in.";
Languages.HelpTexts["variables_create_Colour"]      = "create colour";
Languages.HelpTexts["variables_get_Colour"]         = "get colour";
Languages.HelpTexts["variables_set_Colour"]         = "set colour to";
//overig/ongebruikt \/
Languages.HelpTexts["functions_PrintNums"]          = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";

// other
Blockly.Msg.TXT_TRUE                      = "true";
Blockly.Msg.TXT_FALSE                     = "false";
Blockly.Msg.TXT_ON                        = "on";
Blockly.Msg.TXT_OFF                       = "off";
Blockly.Msg.TXT_CREATE_NUMBER             = "create number";
Blockly.Msg.TXT_CREATE_BOOL               = "create boolean";
Blockly.Msg.TXT_CREATE_COLOUR             = "create colour";
Blockly.Msg.TXT_HELP                      = "Help";
Blockly.Msg.TXT_SAVE                      = "Save";
Blockly.Msg.TXT_LOAD                      = "Load";
Blockly.Msg.TXT_BUILD                     = "Build";
Blockly.Msg.TXT_STOP                      = "Stop";
Blockly.Msg.TXT_START                     = "Start";
Blockly.Msg.TXT_LANGUAGE                  = "language";
Blockly.Msg.TXT_TEST                      = "Test";
Blockly.Msg.TXT_Layout                    = "Lay-out";
Blockly.Msg.TXT_TITLE                     = "Arexx Smart Factory";
Blockly.Msg.TXT_CONNECTED                 = "✔  Connected";
Blockly.Msg.TXT_DISCONNECTED              = "❌  Disconnected";
Blockly.Msg.TXT_ONTIMEOUT                 = "No (good) conection. Arange a good conection or restart the board ";
Blockly.Msg.TXT_ONERROR                   = "Onbekende fout, zie console.";