package com.example.listapp;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.Image;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Display;
import android.widget.ImageView;

public class DetailActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        Intent intent = getIntent();
        int index = intent.getIntExtra("itemIndex", -1);

        if (index > -1) {
            int pic = getImage(index);
            ImageView imageView = (ImageView) findViewById(R.id.imageView);
            scaleImage(imageView, pic);
        }
    }

    private int getImage(int index) {
        switch (index) {
            case 0: return R.drawable.peach;
            case 1: return R.drawable.tomato;
            case 2: return R.drawable.squash;
            default: return -1;
        }
    }

    private void scaleImage(ImageView image, int pic) {
        Display screen = getWindowManager().getDefaultDisplay();
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeResource(getResources(), pic, options);
        int imageWidth = options.outWidth;
        int screenWidth = screen.getWidth();

        if (imageWidth > screenWidth) {
            int ratio = Math.round((float)imageWidth / (float)screenWidth);
            options.inSampleSize = ratio;
        }
        options.inJustDecodeBounds = false;
        Bitmap scaledImage = BitmapFactory.decodeResource(getResources(), pic, options);
        image.setImageBitmap(scaledImage);
    }
}
