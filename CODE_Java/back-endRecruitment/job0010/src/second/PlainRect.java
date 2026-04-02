package second;

public class PlainRect extends Rect{
    double startX;
    double startY;

    public PlainRect(){
        this.height=this.width=this.startX=this.startY=0;
    }

    public PlainRect(double startX,double startY,double width,double height){
        this.height=height;
        this.width=width;
        this.startX=startX;
        this.startY=startY;
    }

    public boolean isInside(double x,double y){
        if(x>=startX&&x<=startX+width){
            if(y>=startY&&y<=startY+height){
                return true;
            }
        }
        return false;
    }
}
