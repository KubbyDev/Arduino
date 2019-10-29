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
        drawMap();
    }

    public void drawMap() {

        Canvas canvas = surfaceHolder.lockCanvas();

        paint.setColor(Color.argb(255, (int)(Math.random()*255), 0, 0));
        canvas.drawRect(0,0,672,672,paint);

        surfaceHolder.unlockCanvasAndPost(canvas);
    }
}
