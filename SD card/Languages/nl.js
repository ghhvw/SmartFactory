"use strict";

var Languages = {};
Languages.BlockNames = {};
Languages.HelpTexts = {};

// categories
Blockly.Msg.CAT_LOGIC                     = "Logica";
Blockly.Msg.CAT_LOOPS                     = "Lussen";
Blockly.Msg.CAT_TIME                      = "Tijd";
Blockly.Msg.CAT_MATH                      = "Wiskunde";
Blockly.Msg.CAT_MOVEMENT                  = "Beweging";
Blockly.Msg.CAT_IO                        = "I/O";
Blockly.Msg.CAT_VARIABLES                 = "Variabelen";

// variables
Blockly.Msg.VAR_BOOL                      = "Boolean";
Blockly.Msg.VAR_NUMBER                    = "Getal";
Blockly.Msg.VAR_COLOUR                    = "Kleur";

// hardcoded blocks text
Blockly.Msg.BL_IF_ELSE_IF                 = "als";
Blockly.Msg.BL_IF_ELSE_THEN               = "doe";
Blockly.Msg.BL_IF_ELSE_ELSE               = "anders doe";
Blockly.Msg.BL_NEGATE                     = "niet %1";
Blockly.Msg.BL_LED                        = "zet LED %1 %2";
Blockly.Msg.BL_BUTTON                     = "knop %1 is ingedrukt";
Blockly.Msg.BL_WHILE					  = "zolang %1 herhaal %2";
Blockly.Msg.BL_REPEAT_TIMES				  = "voor %1 keer";
Blockly.Msg.BL_REPEAT_DO				  = "herhaal";
Blockly.Msg.BL_REPEAT_FOREVER			  = "herhaal voor altijd";

// jumptable blocks
Blockly.Msg.BL_WAIT_MS                    = "wacht voor %1 milliseconden";
Blockly.Msg.BL_WAIT_1_SEC                 = "wacht voor 1 seconde";
Blockly.Msg.BL_MOVE_TO_IDLE               = "ga naar rust positie";
Blockly.Msg.BL_MOVE_TO_UP                 = "ga naar omhoog positie";
Blockly.Msg.BL_PRINT_NUMBER               = "print getal %1";
Blockly.Msg.BL_INVERT                     = "-%1";
Blockly.Msg.BL_WAIT_REACHED               = "wacht tot het doel is bereikt";
Blockly.Msg.BL_ENABLE_SERVOS              = "zet servos aan %1";
Blockly.Msg.BL_SET_JOINT                  = "beweeg %1 naar %2";
Blockly.Msg.BL_MOVE_SMOOTH                = "ga naar %1° %2° %3° %4° %5° %6°";
Blockly.Msg.BL_ADD                        = "%1 + %2";
Blockly.Msg.BL_SUBTRACT                   = "%1 - %2";
Blockly.Msg.BL_MULTIPLY                   = "%1 * %2";
Blockly.Msg.BL_DIVIDE                     = "%1 / %2";
Blockly.Msg.BL_EQUAL                      = "%1 == %2";
Blockly.Msg.BL_BIGGER                     = "%1 > %2";
Blockly.Msg.BL_SMALLER                    = "%1 < %2";
Blockly.Msg.BL_BIGGER_OR_EQUAL            = "%1 >= %2";
Blockly.Msg.BL_SMALLER_OR_EQUAL           = "%1 <= %2";
Blockly.Msg.BL_OR                         = "%1 of %2";
Blockly.Msg.BL_AND                        = "%1 en %2";
Blockly.Msg.BL_XOR                        = "een van %1 en %2";
Blockly.Msg.BL_TOGGLELED                  = "toggle LED";
Blockly.Msg.BL_SETLED                     = "LED %1";
Blockly.Msg.BL_DIGITALREAD                = "lees digitaal %1";
Blockly.Msg.BL_MOVEBELT                   = "beweeg band %2 %1";
Blockly.Msg.BL_STOPBELT                   = "stop band %1";
Blockly.Msg.BL_MOVESORTERARMDISTANCE      = "sorteer arm %1 %2 positie(s)";
Blockly.Msg.BL_MOVESORTERARMINDEX         = "sorteer arm naar %1";
Blockly.Msg.BL_SORTERARMPOSITION          = "sorteer arm positie";
Blockly.Msg.BL_SORTERARMREADY             = "sorteer arm is klaar";
//Blockly.Msg.BL_MOVESORTERARM              = "beweeg sorteer arm %1";
//Blockly.Msg.BL_STOPSORTERARM              = "stop sorteer arm";
Blockly.Msg.BL_MOVETURNTABLE              = "draai draaischijf %2 %1";
Blockly.Msg.BL_STOPTURNTABLE              = "stop draaischijf %1";
Blockly.Msg.BL_MOVEELEVATOR               = "beweeg lift %1";
Blockly.Msg.BL_STOPELEVATOR               = "stop lift";
Blockly.Msg.BL_ELEVATORREADY              = "lift is klaar";
Blockly.Msg.BL_SOLENOID                   = "solenoïde nr.%1 %2";
Blockly.Msg.BL_PULSESOLENOID              = "solenoïde nr.%1 puls";
Blockly.Msg.BL_ANALOGREAD                 = "lees analoog %1";
Blockly.Msg.BL_READSHARPSENSOR            = "sharp sensor %1";
Blockly.Msg.BL_OPTOCOUPLERREAD            = "lees optocoupler %1";
Blockly.Msg.BL_SELECTCOLOUR               = "%1";
Blockly.Msg.BL_READCOLOURSENSOR           = "kleursensor";
Blockly.Msg.BL_COMPARECOLOURS             = "kleur %1 == kleur %2";
Blockly.Msg.BL_SETRELAY                   = "Stel relais %2 in als %1";

// hardcoded blocks help
//logic
Languages.BlockNames["controls_simple_if"]          = "als-doe";
Languages.BlockNames["controls_ifelse"]             = "als-doe-anders doe";
Languages.BlockNames["Logic_boolean"]               = "waar/onwaar : boolean";
Languages.BlockNames["logic_negate"]                = "niet : logische inverter";
Languages.BlockNames["functions_or"]                = "of";
Languages.BlockNames["functions_and"]               = "en";
Languages.BlockNames["functions_xor"]               = "een van-en : exlusieve of";
//loops
Languages.BlockNames["controls_repeat_ext"]         = "voor-keer-herhaal";
Languages.BlockNames["controls_while"]              = "zolang-herhaal";
Languages.BlockNames["controls_repeat_forever"]     = "herhaal voor altijd";
//time
Languages.BlockNames["functions_wait_ms"]           = "wacht voor n milliseconden";
Languages.BlockNames["functions_wait1sec"]          = "wacht voor 1 seconde";
//math
Languages.BlockNames["math_number"]                 = "0 : getal";
Languages.BlockNames["functions_invert"]            = "- : negatief";
Languages.BlockNames["functions_add"]               = "+ : optellen";
Languages.BlockNames["functions_subtract"]          = "- : min";
Languages.BlockNames["functions_multiply"]          = "* : keer";
Languages.BlockNames["functions_divide"]            = "/ : delen";
Languages.BlockNames["functions_equal"]             = "== : is gelijk aan";
Languages.BlockNames["functions_bigger"]            = "> : is groter dan";
Languages.BlockNames["functions_smaller"]           = "< : is kleiner dan";
Languages.BlockNames["functions_biggerOrEqual"]     = ">= : is groter of gelijk aan";
Languages.BlockNames["functions_smallerOrEqual"]    = "<= : is kleiner of gelijk aan";
Languages.BlockNames["functions_CompareColours"]    = "kleur-== kleur-";
//movement
Languages.BlockNames["functions_MoveBelt"]			= "beweeg band";
Languages.BlockNames["functions_StopBelt"]			= "stop band";
Languages.BlockNames["functions_MoveSorterArmDistance"] = "sorteer arm--positie(s)";
Languages.BlockNames["functions_MoveSorterArmIndex"] = "sorteer arm naar-";
Languages.BlockNames["functions_SorterArmPosition"]	= "sorteer arm positie";
Languages.BlockNames["functions_SorterArmReady"]	= "sorteer arm is klaar";
Languages.BlockNames["functions_MoveTurntable"]		= "draai draaischijf";
Languages.BlockNames["functions_StopTurntable"]		= "stop draaischijf";
Languages.BlockNames["functions_MoveElevator"]		= "beweeg lift";
Languages.BlockNames["functions_StopElevator"]		= "stop lift";
Languages.BlockNames["functions_ElevatorReady"]		= "lift is klaar";
Languages.BlockNames["functions_Solenoid"]			= "solenoïde nr.-";
Languages.BlockNames["functions_PulseSolenoid"]		= "solenoïde nr.-pulse";
//io
Languages.BlockNames["functions_SelectColour"]      = "kleur";
Languages.BlockNames["io_button"]                   = "knop-is ingedrukt";
Languages.BlockNames["io_led"]                      = "zet LED-aan/uit";
Languages.BlockNames["functions_ToggleLED"]			= "toggle LED";
Languages.BlockNames["functions_LED"]               = "LED aan/uit";
Languages.BlockNames["functions_DigitalRead"]		= "lees digitaal";
Languages.BlockNames["functions_AnalogRead"]		= "lees analoog";
Languages.BlockNames["functions_ReadSharpSensor"]	= "sharp sensor";
Languages.BlockNames["functions_OptocouplerRead"]	= "lees optocoupler";
Languages.BlockNames["functions_ReadColourSensor"]  = "kleursensor";
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
Languages.BlockNames["functions_MoveSorterArm"]		= "beweeg sorteer arm";
Languages.BlockNames["functions_StopSorterArm"]		= "stop sorteer arm";
Languages.BlockNames["functions_moveToIdle"]        = "ga naar rust positie";
Languages.BlockNames["functions_moveToUp"]          = "ga naar rechtop positie";
Languages.BlockNames["functions_PrintNums"]         = "print getal";
Languages.BlockNames["functions_waitReached"]       = "wacht tot positie is bereikt";
Languages.BlockNames["functions_enableServos"]      = "servo's aanzetten";
Languages.BlockNames["functions_setJoint"]          = "zet joint";
Languages.BlockNames["functions_moveSmooth"]        = "beweeg geleidelijk";

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
Languages.HelpTexts["functions_MoveSorterArmDistance"] = "Beweeg de sorteer arm een aantal posities naar links of naar rechts.";
Languages.HelpTexts["functions_MoveSorterArmIndex"] = "Beweeg de sorteer arm naar een positie.";
Languages.HelpTexts["functions_SorterArmPosition"]  = "Lees de positie van de sorteer arm.";
Languages.HelpTexts["functions_SorterArmReady"]     = "Sorteer arm is klaar voor een nieuwe beweging.";
Languages.HelpTexts["functions_MoveTurntable"]		= "Beweeg de draaischijf linksom of rechtsom.";
Languages.HelpTexts["functions_StopTurntable"]		= "Stop de draaischijf.";
Languages.HelpTexts["functions_MoveElevator"]		= "Beweeg de lift, hij stopt automatisch. Gebruik blok \"" + Languages.BlockNames["functions_ElevatorReady"] + "\" om te checken of de lift klaar is.";
Languages.HelpTexts["functions_StopElevator"]		= "Stop de lift.";
Languages.HelpTexts["functions_ElevatorReady"]		= "Geeft \"waar\" terug wanneer de lift klaar is met bewegen.";
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
Languages.HelpTexts["functions_MoveSorterArm"]		= "Beweeg de sorteerarm naar links of naar rechts. Let erop dat deze niet automatisch stopt, dus je moet er voor zorgen dat de arm stopt wanneer één van de schakelaars is ingedrukt. Bekijk het \"" + Languages.BlockNames["functions_DigitalRead"] + "\" blok.";
Languages.HelpTexts["functions_StopSorterArm"]		= "Stop de sorteerarm.";
Languages.HelpTexts["functions_PrintNums"]          = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";

// other
Blockly.Msg.TXT_TRUE                      = "waar";
Blockly.Msg.TXT_FALSE                     = "onwaar";
Blockly.Msg.TXT_ON                        = "aan";
Blockly.Msg.TXT_OFF                       = "uit";
Blockly.Msg.TXT_CREATE_NUMBER             = "maak getal";
Blockly.Msg.TXT_CREATE_BOOL               = "maak boolean";
Blockly.Msg.TXT_CREATE_COLOUR             = "maak kleur";
Blockly.Msg.TXT_HELP                      = "Help";
Blockly.Msg.TXT_SAVE                      = "Opslaan";
Blockly.Msg.TXT_LOAD                      = "Inladen";
Blockly.Msg.TXT_BUILD                     = "Bouw";
Blockly.Msg.TXT_START                     = "Start";
Blockly.Msg.TXT_LANGUAGE                  = "taal";
Blockly.Msg.TXT_TEST                      = "Test";
Blockly.Msg.TXT_TITLE                     = "Arexx Robot Arm";
Blockly.Msg.TXT_CONNECTED                 = "✔️Verbonden";
Blockly.Msg.TXT_DISCONNECTED              = "❌Niet verbonden";
Blockly.Msg.TXT_ONTIMEOUT                 = "Geen (goede) verbinding. Zorg voor een goede WiFi verbinding of start het bord opnieuw op.";
Blockly.Msg.TXT_ONERROR                   = "Onbekende fout, zie console.";