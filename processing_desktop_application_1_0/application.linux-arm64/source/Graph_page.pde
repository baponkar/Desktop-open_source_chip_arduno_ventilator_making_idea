class Graph{
  int vNo,hNo;
  color c;
  float xPos,yPos,w,h,lxVal,hxVal,lyVal,hyVal;
  String xLabel,yLabel;
  PFont font;
  
  
  Graph(float tempxPos, float tempyPos,float tempw,float temph,int tempvNo,int temphNo,color tempc,float lx,float hx, float ly, float hy){
    font = createFont(PFont.list()[0],30);
    
    xPos = tempxPos;
    yPos = tempyPos;
    w = tempw;
    h = temph;
    vNo = tempvNo;
    hNo = temphNo;
    c = tempc;
    lxVal = lx;
    hxVal = hx;
    lyVal = ly;
    hyVal = hy;
    textSize(w*.015);
  }
  
  
  void display(String tempx, String tempy){
    stroke(c);
    fill(c);
    strokeWeight(.5);
    float ySpace = h/hNo;
    float xSpace = w/vNo;
    float xValSpace = (hxVal-lxVal)/(vNo);
    float yValSpace = (hyVal-lyVal)/(hNo);
    xLabel = tempx;
    yLabel = tempy;
    h = ySpace*hNo;
    w = xSpace*vNo;
    
    //ylabels
    pushMatrix();
    textAlign(CENTER);
    translate(xPos-40, yPos+h/2);
    rotate(3*PI/2);     
    text(yLabel,0,0);
    popMatrix();
    //xlabels
    pushMatrix();
    textAlign(CENTER);
    translate(xPos+w/2, yPos+h+40);
    rotate(0);     
    text(xLabel,0,0);
    popMatrix();
    
    //Making vertical lines
    for(int i =0;i<vNo+1;i++){
      if(i == vNo/2 || i== 0 || i == vNo){
        fill(0,127,155);
        stroke(0,127,255);
      }
      else{
        stroke(c);
        fill(c);
      }
      
      line(xPos +i*xSpace,yPos,xPos+i*xSpace,yPos+h);
      float valx = xValSpace*i;
       String valx1 = nf(valx,0,1);//making one decimal approximation
       if(i%4 == 0){
         text(valx1,xPos + i*xSpace,yPos+h+20);//showing values along x axis
       }
   }
   
   //Making horizontal lines/*
    for(int j=0;j<hNo+1;j++){
       if(j == hNo/2|| j== 0 || j== hNo){
        fill(0,127,255);
        stroke(0,127,155);
      }
      else{
        stroke(c);
        fill(c);
      }
      
    line(xPos,yPos+j*ySpace,xPos+w,yPos+j*ySpace);
    float valy = lyVal+yValSpace*j;
     String valy1 = nf(valy,0,1);//making one decimal approximation
     text(valy1,xPos-20,yPos+j*ySpace);//showing values in y axis
     
  }
 }
}
