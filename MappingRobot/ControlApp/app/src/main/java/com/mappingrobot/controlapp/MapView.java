package com.mappingrobot.controlapp;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class MapView extends SurfaceView {

    private Paint paint;
    private SurfaceHolder surfaceHolder;

    public MapView(Context context, AttributeSet attr) {
        super(context, attr);
        paint = new Paint();
        paint.setStyle(Paint.Style.FILL_AND_STROKE);
        surfaceHolder = getHolder();
    }

    public void updateDisplay() {

        Canvas canvas = surfaceHolder.lockCanvas();

        paint.setColor(Color.argb(255, 127, 127, 127));
        canvas.drawRect(0,0,RobotMap.SIZE*9,RobotMap.SIZE*9,paint);

        paint.setColor(Color.argb(255, 0, 0, 0));
        for(int y = 0; y < RobotMap.SIZE; y++)
            for(int x = 0; x < RobotMap.SIZE; x++)
                if(RobotMap.get(x, y))
                    canvas.drawRect(x*9, y*9, x*9+9, y*9+9, paint);

        surfaceHolder.unlockCanvasAndPost(canvas);
    }
}
