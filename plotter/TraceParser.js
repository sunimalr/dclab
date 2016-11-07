var minimumStart = 99999999999; //[99999999999,99999999999,99999999999,99999999999];
var maximumStart =0;// = [0,0,0,0];

function parseTrace(lines){
	  var entries = {};
	  
    for(var line = 0; line < lines.length; line++){

      	if(!lines[line]){
      		continue;
      	}

      	var words = lines[line].split(',');

      	// console.log(words);
      	if(words.length != 7){
      		console.log("entry length is not 7!, not parsing");
      		return;
      	}

      	var cpu = parseInt(words[0]);
        var pid = parseInt(words[1],16);
      	var starttime = parseInt(words[2]);
      	var endtime = parseInt(words[3]);
      	var duration = parseInt(words[4]);
        if(duration==0)
          duration=200;
      	var type = parseInt(words[5],16);//Hex to integer
      	var name = words[6];

      	if(minimumStart>starttime){
      		minimumStart=starttime;
      	}
      	if(maximumStart<starttime){
      		maximumStart=starttime;
      	}

      	if(!(cpu in entries)){
      		entries[cpu] = {}; 
      	}

        if(!(pid in entries[cpu])){
           entries[cpu][pid] = [];
        }

      	entries[cpu][pid].push([cpu,starttime,endtime,duration,type,name]);
      	//console.log(starttime);
    }
    console.log(minimumStart);
    console.log(entries);
    //console.log(minimumStart[0] + " , " + minimumStart[1] + " , " + minimumStart[2] + " , " + minimumStart[3]);
    //console.log("finalpoint : "+maximumStart);
    return entries;
}
