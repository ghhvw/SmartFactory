"use strict";


// ----------------------------------------------------------
//	The instructions for the AVR
// ----------------------------------------------------------
var instructions = 
{
adc:
    {
        name: "Add with Carry",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x1C00,tokens[1],tokens[2]); 
        } 
    },
add:
    {
        name: "Add without Carry",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x0C00,tokens[1],tokens[2]); 
        } 
    },
and:
    {
        name: "and",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x2000,tokens[1],tokens[2]); 
        } 
    },
andi:
    {
        name: "logical AND with immediate",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.immediateInst(0x7000,tokens[1],tokens[2]); 
        } 
    },
brbs:
    {
        name: "Branch if Bit in SREG is Set",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.sregBranchInstr(0xF000,tokens[2],tokens[1],address); 
        } 
    },
breq:
    {
        name: "Branch if Equal",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        {
            return InstGen.sregBranchInstr(0xF000,tokens[1],'1',address); 
        } 
    },
brne:
    {
        name: "Branch if Equal",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        {
            return InstGen.sregBranchInstr(0xF400,tokens[1],'1',address); 
        } 
    },
cbi:
    {
        name: "Clear Bit in I/O Register",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.IoBitInst(0x9800,tokens[1],tokens[2]); 
        } 
    },
call:
    {
        name: "Long Call to a Subroutine",
        words: 2,
        params: 1,
        getCode: function(address, tokens)
        { 
            return InstGen.jumpInstr(0x940E0000, tokens[1]); 
        }
    },
clr:
    {
        name: "Clear Register",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x2400,tokens[1],tokens[1]); 
        } 
    },
dec:
    {
        name: "Decrement",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        {
            return InstGen.singleRegInstr(0x940A,tokens[1]); 
        } 
    },
eor:
    {
        name: "Exclusive OR",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x2400,tokens[1],tokens[2]); 
        } 
    },
inc:
    {
        name: "Increment",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        {
            return InstGen.singleRegInstr(0x9403,tokens[1]); 
        } 
    },
sub:
    {
        name: "subtract",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x1800,tokens[1],tokens[2]); 
        }
    },
ldi:
    {
        name: "load immediate",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.immediateInst(0xE000,tokens[1],tokens[2]); 
        }
    },
or:
    {
        name: "or",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x2800,tokens[1],tokens[2]); 
        }
    },
in:
    {
        name: "Load an I/O Location to Register",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.ioInst(0xB000,tokens[1],tokens[2]);
        }
    },
out:
    {
        name: "Store Register to I/O Location",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.ioInst(0xB800,tokens[2],tokens[1]);
        } 
    },
rjmp:
    {
        name: "relative jump",
        words: 1,
        params: 1,
        getCode: function(address, tokens){ console.log("instruction rjmp not yet implemented") },    // 1100 xxxx xxxx xxxx relative jump in words
    },
jmp:
    {
        name: "Jump",
        words: 2,
        params: 1,
        getCode: function(address, tokens)
        { 
            return InstGen.jumpInstr(0x940c0000, tokens[1]); 
        }
    },
lds:
    {
        name: "Load Direct from Data Space",
        words: 2,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.ramInstr(0x90000000,tokens[2],tokens[1]); 
        } 
    },
mov:
		{
				name: "Copy Register",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        { 
            return InstGen.twoRegInst(0x2C00, tokens[1], tokens[2]); 
        }
		},
movw:
		{
				name: "Copy Register Word",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        { 
            return InstGen.twoWordInst(0x0100, tokens[1], tokens[2]); 
        }
		},
pop:
    {
        name: "Pop Register from Stack",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        { 
            return InstGen.singleRegInstr(0x900F, tokens[1]); 
        }
    },
push:
    {
        name: "Push Register on Stack",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        { 
            return InstGen.singleRegInstr(0x920F, tokens[1]); 
        }
    },
sbc:
    {
        name: "Subtract with Carry",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x0800,tokens[1],tokens[2]); 
        } 
    },
sbi:
    {
        name: "Set Bit in I/O Register",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.IoBitInst(0x9A00,tokens[1],tokens[2]); 
        } 
    },
sbis:
    {
        name: "Skip if Bit in I/O Register is Set",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.IoBitInst(0x9B00,tokens[1],tokens[2]); 
        } 
    },
sbic:
    {
        name: "Skip if Bit in I/O Register is Cleared",
        words: 1,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.IoBitInst(0x9900,tokens[1],tokens[2]); 
        } 
    },
sts:
    {
        name: "Store Direct to Data Space",
        words: 2,
        params: 2,
        getCode: function(address, tokens)
        {
            return InstGen.ramInstr(0x92000000,tokens[1],tokens[2]); 
        } 
    },
tst:
    {
        name: "Test for Zero or Minus",
        words: 1,
        params: 1,
        getCode: function(address, tokens)
        {
            return InstGen.twoRegInst(0x2000,tokens[1],tokens[1]); 
        } 
    }
};




var InstGen = {};

InstGen.twoRegInst = function(base, register1, register2)
{
    register1 = parseRegister(register1);
    register2 = parseRegister(register2);
    
    if(register1 > 31 || register2 > 31) 
        throwError("?","invalid register number");
    
    base |= register1 << 4;
    base |= ((register2 & 0x10) << 5) | register2 & 0xF;
    return wordToHexCode(base);
}


InstGen.twoWordInst = function(base, register1, register2)
{
    register1 = parseRegister(register1);
    register2 = parseRegister(register2);
    
    if(register1 > 31 || register2 > 31) 
        throwError("?","invalid register number");
    
    base |= (register1 % 0x1E) << 3;
    base |= ((register2 & 0x1E) >>> 1);
    return wordToHexCode(base);
}



InstGen.immediateInst = function(base, register, num)
{
    register = parseRegister(register);
    
    if(register > 31 || register < 16) 
        throwError("?","invalid register number");
    
    num = parseNumber(num);
    
    base |= (0xF & register) << 4;
    base |= ((0xF0 & num)<<4) | (0xF & num);
    return wordToHexCode(base);
}


InstGen.ioInst = function(base, register, ioAddress)
{
    register = parseRegister(register);
    
    if(register > 31) 
        throwError("?","invalid register number");
    
    ioAddress = parseNumber(ioAddress);
    
    if(ioAddress > 63)
        throwError("?","IO address out of range");
    
    base |= register << 4;
    base |= ((ioAddress & 0x30) << 5) | (ioAddress & 0xF);
    return wordToHexCode(base);
}


InstGen.IoBitInst = function(base, ioAddress, bit)
{  
    ioAddress = parseNumber(ioAddress);
    
    if(ioAddress > 31 || ioAddress < 0)
        throwError("?","IO address out of range");
    
		bit = parseNumber(bit);
	
		if(bit > 7 || bit < 0)
			throwError("?","bit number out of range"); 
			
    base |= ioAddress << 3;
    base |= bit;
    return wordToHexCode(base);
}


InstGen.jumpInstr = function(base, address)
{
    address = parseAddress(address);
    
    if(address > Config.deviceMemory)
        throwError('?',"address out of range");
    
    base |= ((0x3E0000 & address) << 3) | (0x1ffff & address);
    return wordToHexCode(base >>> 16)+wordToHexCode(base & 0xFFFF);
}


InstGen.sregBranchInstr = function(base, targetAddress, bit, currentAddress)
{
    bit = parseNumber(bit);
    if(bit > 7 || bit < 0)
        throwError('?', "number out of range");
    
    
    targetAddress = parseAddress(targetAddress);
    var addressDelta = targetAddress - currentAddress-1;
        
    if(addressDelta > 63 || addressDelta < -64)
        throwError('?',"target address out of range");
    
    if(addressDelta < 0)
    {
        console.log(addressDelta);
        addressDelta++;
    }
    addressDelta &= 0x7F;
    
    base |= bit;
    base |= addressDelta << 3;
    return wordToHexCode(base);
}





InstGen.singleRegInstr = function(base, register)
{
    if(!register.toLowerCase().startsWith('r'))
        throwError("?","unexpected token");
    
    register = parseInt(register.substring(1), 10);
    
    if(register > 31)
        throwError("?","invalid register number");
    
    base |= register << 4;
    return wordToHexCode(base);
}



InstGen.twosComplement = function(num)
{
    if(num >= 0)
    {
        return num;
    }
    else
    {
        return ((~num)+1)&0xFF;
    }
}



InstGen.ramInstr = function(base, ramAddress, register)
{
		register = parseRegister(register);
		if(register > 31 || register < 0)
        throwError("?","invalid register number");
		
		ramAddress = parseRamAddress(ramAddress);
	
		base |= ramAddress & 0xFFFF;
		base |= (register & 0x1F) << 20;
	
		return wordToHexCode(base >>> 16)+wordToHexCode(base & 0xFFFF);
}




// ----------------------------------------------------------
//	Device Configuration
// ----------------------------------------------------------
var Config = {}

Config.deviceMemory = 32000;


// ----------------------------------------------------------
//	Assembler logic
// ----------------------------------------------------------
var startAddress = 0x0000;

var labels = {};
var equs   = {};
var defs   = {};


function assemble(assembly) 
{
    labels  = {};
    equs    = {};
    defs    = {};
   
    var text = assembly;
    
    // split lines
    var re=/\r\n|\n\r|\n|\r/g;
    var lines= text.replace(re,"\n").split("\n");
    
    // assebmle the lines
    var machineCode = assembleLines(lines);
    
    return machineCode;
}




function assembleLines(lines)
{
    var address = startAddress;
    var opCodes = [];
  	var memoryUsed = 0;  
	
    // -------------------------------------------
    //      Step 1: remove comments and generate list of opcodes, labels, .equs and .defs
    // -------------------------------------------
    for(var i = 0; i < lines.length; i++)
    {
        var line = lines[i];
        
        // remove comments
        var commentIndex = line.indexOf(';');
        if(commentIndex == 0)
        {
            lines[i] = '';
            line = '';
        }
        else if(commentIndex > 0) 
        {
            lines[i] = line.substring(0,commentIndex);
        }
        
        // if this is an empty line continue with the next one
        if(line.trim().length > 0)
        {
            // check if this is a label
            var colonIndex = line.indexOf(':');

            if(colonIndex > 0)
            {
                labels[line.substring(0,colonIndex)] = address;
            }
            // otherwise split the line into tokens
            else 
            {
                // split the line into tokens
                var tokens = line.replace(',',' ').trim().split(/\s+/g);
                
                // check if this is an assebler directive
                if(tokens[0].startsWith('.'))
                {
                    var directive = tokens[0].toLowerCase();
                    
                    if(directive == ".org")
                    {
                        address = parseNumber(tokens[1]);
                    }
                    else if(directive == ".equ")
                    {
                        var temp = line.trim().substr(5).trim();
                        temp = temp.split('=');
                        if(temp.length > 2)
                            throwError('?', 'wrong syntax for .equ');
                        equs[temp[0].trim()] = temp[1].trim();
                    }
                    else if(directive == ".def")
                    {
                        var temp = line.trim().substr(5).trim();
                        temp = temp.split('=');
                        if(temp.length > 2)
                            throwError('?', 'wrong syntax for .def');
                        defs[temp[0].trim()] = temp[1].trim();
                    }
                }
                // if it isn't assume it's an instruction
                else
                {
                    var instruction = instructions[tokens[0]];

                    // check if instrucion exists 
                    if(instruction != undefined)
                    {
                        var opCode = {};
                        opCode.address = address;
                        opCode.tokens = tokens;
                        opCodes.push(opCode);
                        address += instruction.words;
				        memoryUsed += instruction.words;
                    }
                    else
                    {
                        throwError(i, "instruction "+tokens[0]+" does not exist");
                        return;
                    }
                }
            }   
        }
    }
    
    
    // -------------------------------------------
    //  step 2: generate the actual opcodes and make a list of words
    // -------------------------------------------
    var address = 0;
  	var words = [];  
	
    for(var i = 0; i < opCodes.length; i++)
    {   
        var instruction = instructions[opCodes[i].tokens[0]];
    
        // check if the instruction has the right number of parameters
        if(instruction.params != (opCodes[i].tokens.length-1))
        {
            throwError(i, "Wrong number of parameters. Expected " + instruction.params + " but received " + (opCodes[i].tokens.length-1) + ".");
            return;
        }
        
        // get the instuction machine code
        var hexCode = instruction.getCode(opCodes[i].address, opCodes[i].tokens);
       	for(var j = 0; j < instruction.words; j++)
				{
						var word = {};
						word.address = opCodes[i].address + j;
						word.value = hexCode.substr(j*4, j*4+4);
						words.push(word);
				}
			
        //machinecode += wordToHexText(opCodes[i].address) + ": " + hexCode + "\n";
    }
    
    var percentageMemoryUsed = 100*memoryUsed/((Config.deviceMemory/2)-blocklyAddress); 
    
    // ------------------------------------------------------------
    //  Step 3: Put the words into intel hex file format
    // ------------------------------------------------------------
    var hexFileString = createHexFile(words);  
  
    
    return {hex: hexFileString, percentage: percentageMemoryUsed};
}








function createHexFile(words)
{
		var hexFileText = ':020000020000FC';	// all memory is below 0x10000
		var line = '';
		var previousAddress = -100;
		var lineLength = 0;
		var checksum = 0;
	
		// loop through all the words
		for(var i = 0; i < words.length; i++)
		{
				var word = words[i];
			
				if(word.address != previousAddress+1 || lineLength >= 0x10)
				{
						//handle previous line
						if(i != 0)
						{
							line = line.replace("XX", byteToHex(lineLength));
							checksum += lineLength;
						line += byteToHex((0-checksum) & 0xFF);
						hexFileText += '\n' + line;
						}
					
						//start the next line
						line = ":XX"+wordToHexText(2*word.address)+"00";
						lineLength = 0;
						checksum = addBytesOfWord(2*word.address);
				}
				
				line += word.value;
				checksum += addBytesOfWord( parseInt(word.value, 16) );
				previousAddress = word.address;
				lineLength+=2;
		}
	
		// handle the last line
		if(line != '')
		{
				line = line.replace("XX", byteToHex(lineLength));
				checksum += lineLength;
				line += byteToHex((0-checksum) & 0xFF);
				hexFileText += '\n' + line;
		}
	
		hexFileText += "\n:00000001FF";
	
		return hexFileText;
}



function throwError(line, message)
{
    //window.alert("Error at line "+ (line+1) + ": "+message);
    console.log(message);
}



function addBytesOfWord(word)
{
		return (word & 0xFF) + ((word >> 8) & 0xFF)
}

var hexLookup = ['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'];



function byteToHex(hex)
{
    hex = hex & 0xFF;
    return hexLookup[(hex >>> 4)] + hexLookup[0xF & hex];
}


function wordToHexText(hex)
{
    return hexLookup[0xF & (hex >>> 12)] + hexLookup[0xF & (hex >>> 8)] + hexLookup[0xF & (hex >>> 4)] + hexLookup[0xF & hex];
}


function wordToHexCode(hex)
{
    return hexLookup[0xF & (hex >>> 4)] + hexLookup[0xF & hex] + hexLookup[0xF & (hex >>> 12)] + hexLookup[0xF & (hex >>> 8)];
}


function parseNumber(num)
{
    var ret = parseInt(num);
    
    if(isNaN(ret))
    {
        // check if this is a def or equ
        if(equs[num] != undefined)
            ret = parseInt(equs[num]);
        // otherwise throwerror
        else
            return NaN;
    }
    
    return ret;
}


function parseRegister(register)
{
    // check for defs
    if(defs[register] != undefined)
        register = defs[register];
    
    if(!register.toLowerCase().startsWith('r'))
        throwError("?","unexpected token"); 
    
    register = parseInt(register.substring(1), 10);
    
    if(register > 31)
        throwError("?","invalid register number");
    
    return register;
}



function parseAddress(text)
{
    var address = parseInt(text);
   	
    if(isNaN(address))
    {       
        // see if this text is defined as a label
        address = labels[text];
    		if(address == undefined)
				{
					address = equs[text];
				}
		}  
	
    return address;
}


function parseRamAddress(text)
{
		var address = parseInt(text);
   	
    if(isNaN(address))
    {       
				address = equs[text];
		}  
	
    return address;
}


function swapBytes(word)
{
    if(word.length != 4)
        throwError("coding mistake: word must be 4 characters long.");
    
    return word.substring(2,4) + word.substr(0,2);
}