// Draw a width * height rectangle with color at position (x, y).

function colorRGB(colorName) {
	if (colorName == "blue") return "rgb(0,0,255)";
	if (colorName == "red") return "rgb(255,0,0)";
	if (colorName == "green") return "rgb(0,255,0)";
	if (colorName == "black") return "rgb(0,0,0)";
	if (colorName == "white") return "rgb(250,255,255)";
	return "rgb(0,0,0)";
}

function drawSubRectangle1(x, y, width, height, color) {
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + color + ";stroke-width:3\" />"
}

function drawSubRectangle2(x, y, width, height, color) {
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + color + ";stroke-width:3\" />"
}

function drawSubRectangle3(x, y, width, height, color) {
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + color + ";stroke-width:3\" />"
}

function drawLine(x, y, width, height) {
	var color=colorRGB("black")
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + colorRGB(color) + ";stroke-width:3\" />"
}

function drawTicks(x, y, width, height) {
	var color="white";
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + colorRGB(color) + ";stroke-width:3\" />"
}

function drawRectangle(x, y, width, eventCode){

	

	var h1=40;
	var h2=24;
	var h3=8;
	var y1=y;
	var y2=y+(h1-h2)/2;
	var y3=y+(h1-h3)/2;
	var c1=getColor1(eventCode);
	var c2=getColor2(eventCode);
	var c3=getColor3(eventCode);

	var recContent;

	recContent=drawSubRectangle1(x,y1,width,h1,c1);
	recContent=recContent+drawSubRectangle2(x,y2,width,h2,c2);
	recContent=recContent+drawSubRectangle3(x,y3,width,h3,c3);
	return recContent;	
}

function getColor1(eventCode){
	//Decide outermose color by 1st digit of the evet code
	var firstdigit=eventCode >> 8;

	switch (firstdigit){
		case 2 : return "rgb(0,51,102)";
				break;
		case 3 : return "rgb(0,102,0)";
				break;
		case 4 : return "rgb(102,51,0)";
				break;
		case 5 : return "rgb(204,0,0)";
				break;
		case 6 : return "rgb(204,0,153)";
				break;
		case 7 : return "rgb(0,255,0)";
				break;
		case 8 : return "rgb(255,255,0)";
				break;
		case 9 : return "rgb(255,255,0)";
				break;
		case 10 : return "rgb(0,255,153)";
				break;
		case 11 : return "rgb(0,255,153)";
				break;
		case 12 : return "rgb(255,102,0)";
				break;
		case 13 : return "rgb(255,102,0)";
				break;
	}

	console.log(firstdigit);
}

function getColor2(eventCode){
	var seconddigit=(eventCode >> 4) & 0xF;	

	var red=((seconddigit+5) * 14) % 255;
	var green=((seconddigit+6) * 2) % 128;
	var blue=((seconddigit+7) * 23) % 128;
	var colorString="rgb("+red+","+green+","+blue+")";
	//console.log(colorString); 
	
	switch (seconddigit){
		
		case 0 : return "rgb(96,31,247)";
				break;	
		case 1 : return "rgb(50,0,102)";
				break;
		case 2 : return "rgb(0,51,102)";
				break;
		case 3 : return "rgb(0,102,0)";
				break;
		case 4 : return "rgb(102,51,0)";
				break;
		case 5 : return "rgb(204,0,0)";
				break;
		case 6 : return "rgb(204,0,153)";
				break;
		case 7 : return "rgb(0,255,0)";
				break;
		case 8 : return "rgb(255,255,0)";
				break;
		case 9 : return "rgb(255,255,0)";
				break;
		case 10 : return "rgb(0,255,153)";
				break;
		case 11 : return "rgb(0,255,153)";
				break;
		case 12 : return "rgb(255,102,0)";
				break;
		case 13 : return "rgb(255,102,0)";
				break;
		case 14 : return "rgb(128,23,65)";
				break;
		case 15 : return "rgb(140,140,140)";
				break;	
	}


	//return colorString;
}

function getColor3(eventCode){
	var thirddigit=eventCode & 0xF;	

	var green=((thirddigit+5) * 3) % 255;
	var blue=((thirddigit+6) * 2) % 255;
	var red=((thirddigit+12) * 8) % 255;
	var colorString="rgb("+red+","+green+","+blue+")";
	//console.log(colorString);

	switch (thirddigit){
		
		case 0 : return "rgb(96,31,247)";
				break;	
		case 1 : return "rgb(50,0,102)";
				break;
		case 2 : return "rgb(0,51,102)";
				break;
		case 3 : return "rgb(0,102,0)";
				break;
		case 4 : return "rgb(102,51,0)";
				break;
		case 5 : return "rgb(204,0,0)";
				break;
		case 6 : return "rgb(204,0,153)";
				break;
		case 7 : return "rgb(0,255,0)";
				break;
		case 8 : return "rgb(255,255,0)";
				break;
		case 9 : return "rgb(255,255,0)";
				break;
		case 10 : return "rgb(0,255,153)";
				break;
		case 11 : return "rgb(0,255,153)";
				break;
		case 12 : return "rgb(255,102,0)";
				break;
		case 13 : return "rgb(255,102,0)";
				break;
		case 14 : return "rgb(128,23,65)";
				break;
		case 15 : return "rgb(140,140,140)";
				break;	
	}

	//return colorString;
}


