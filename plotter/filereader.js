
//Event list read from file is processed here to arrange coordinates as necessary
function processCoordinates(eventList){
	
	startTime=(minimumStart/100)*hundredNanotoPixel;
	var end=eventList[eventList.length-1]-startTime;
	var verticalpadding=0;
	

	//eventList.push([1,480,100,0,"line"]);
	for (i = 0; i < eventList.length; i++) {
		//console.log("Process Coords : " + eventList[i][1]);
		switch(eventList[i][0]) {
    		case 0:
    			verticalpadding=100;
        		break;
    		case 1:
        		verticalpadding=200;
        		break;
        	case 2:
        		verticalpadding=300;
        		break;
        	case 3:
        		verticalpadding=400;
        		break;
		}
		eventList[i][1]-=startTime;
		if(eventList[i][1]<startTime){
			//console.log("Start less than 0 : start ="+ startTime + " Event time= " + (eventList[i][1])+startTime);
		}
		eventList[i][1]+=horizontalpadding;
		eventList[i][2]+=verticalpadding;
		var lineEvent=[];
		//console.log(eventList[i][0],eventList[i][1],eventList[i][2],eventList[i][3],eventList[i][4],eventList[i][5]);
	}

	return eventList;

}

//inputlist element [cpu,start,end,duration,hex,name]
//eventlist element [cpu,x,y,duration,hex,name]
function generateCoordinates(inputlist){
	var eventlist=[];
	for (i = 0; i < inputlist.length; i++) {
		inputlist[i][1]=(inputlist[i][1]/100)*hundredNanotoPixel;
		inputlist[i][2]=0;	
		inputlist[i][3]=(inputlist[i][3]/100)*hundredNanotoPixel;
		//console.log(inputlist[i][1],inputlist[i][2],inputlist[i][3]);
	}
	return inputlist;
}