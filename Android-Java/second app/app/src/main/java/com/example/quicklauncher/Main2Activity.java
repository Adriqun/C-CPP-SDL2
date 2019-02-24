package com.example.quicklauncher;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class Main2Activity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        if (getIntent().hasExtra("special_key")) {
            TextView textView = (TextView) findViewById(R.id.textView);
            String text = getIntent().getExtras().getString("special_key");
            textView.setText(text);
        }
    }
}
