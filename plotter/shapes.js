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
		+ height + "\" style=\"fill:" + colorRGB(color) + ";stroke-width:3\" />"
}

function drawSubRectangle2(x, y, width, height, color) {
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + colorRGB(color) + ";stroke-width:3\" />"
}

function drawSubRectangle3(x, y, width, height, color) {
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + colorRGB(color) + ";stroke-width:3\" />"
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

function drawRectangle(x, y, width){
	var h1=40;
	var h2=24;
	var h3=8;
	var y1=y;
	var y2=y+(h1-h2)/2;
	var y3=y+(h1-h3)/2;
	var c1="red";
	var c2="green";
	var c3="blue";

	var recContent;

	recContent=drawSubRectangle1(x,y1,width,h1,c1);
	recContent=recContent+drawSubRectangle2(x,y2,width,h2,c2);
	recContent=recContent+drawSubRectangle3(x,y3,width,h3,c3);
	return recContent;	
}



