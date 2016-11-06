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
      	if(words.length != 6){
      		console.log("entry length is not 6!, not parsing");
      		return;
      	}

      	var cpu = parseInt(words[0]);
      	var starttime = parseInt(words[1]);
      	var endtime = parseInt(words[2]);
      	var duration = parseInt(words[3]);
        if(duration==0)
          duration=200;
      	var type = parseInt(words[4],16);//Hex to integer
      	var name = words[5];

      	if(minimumStart>starttime){
      		minimumStart=starttime;
      	}
      	if(maximumStart<starttime){
      		maximumStart=starttime;
      	}

      	if(!(cpu in entries)){
      		entries[cpu] = [];
      	}
      	entries[cpu].push([cpu,starttime,endtime,duration,type,name]);
      	//console.log(starttime);
    }
    console.log(minimumStart);
    //console.log(minimumStart[0] + " , " + minimumStart[1] + " , " + minimumStart[2] + " , " + minimumStart[3]);
    //console.log("finalpoint : "+maximumStart);
    return entries;
}