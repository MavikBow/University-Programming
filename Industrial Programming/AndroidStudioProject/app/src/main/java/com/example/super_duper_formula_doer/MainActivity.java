package com.example.super_duper_formula_doer;

import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.GestureDetectorCompat;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity{

    private CheckBox checkBox;
    private ImageView imageView;
    private GestureDetectorCompat gestureDetectorCompat;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        checkBox = (CheckBox)findViewById(R.id.checkBox);
        imageView = (ImageView)findViewById(R.id.profile_image);

        this.gestureDetectorCompat = new GestureDetectorCompat(this, new GestureListener());
    }

    private class GestureListener extends GestureDetector.SimpleOnGestureListener {
        @Override
        public boolean onDoubleTap(@NonNull MotionEvent e) {
            if(MainActivity.this.checkBox.isChecked()) {
                Animation rotate = AnimationUtils.loadAnimation(
                        getApplicationContext(), R.anim.rotate
                );
                MainActivity.this.imageView.startAnimation(rotate);
            }
            return super.onDoubleTap(e);
        }
    }

    public void DoTheSuperFormula(View v){
        EditText et1 = (EditText)findViewById(R.id.input1);
        EditText et2 = (EditText)findViewById(R.id.input2);
        EditText et3 = (EditText)findViewById(R.id.input3);
        EditText et4 = (EditText)findViewById(R.id.input4);

        TextView tv1 = (TextView)findViewById(R.id.output_text);

        double val_a = 0;
        double val_b = 0;
        double val_c = 0;
        double val_d = 0;
        double result = 0;
        String res_text = "";
        boolean goodNumbers = false;

        try{
            val_a = Double.parseDouble(et1.getText().toString());
            val_b = Double.parseDouble(et2.getText().toString());
            val_c = Double.parseDouble(et3.getText().toString());
            val_d = Double.parseDouble(et4.getText().toString());
            goodNumbers = true;
        } catch (NumberFormatException e) {
            res_text = "get actual numbers here";
        }

        if(goodNumbers) {
            if (val_b == 0 || val_d == 0) res_text = "You cannot divide by 0";
            else {
                result = (2 * val_a * val_c) / (val_b * val_d) - (val_a * val_c + val_b - val_a);
                res_text = Double.toString(result);
            }
        }

        tv1.setText(res_text);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event){
        gestureDetectorCompat.onTouchEvent(event);
        return super.onTouchEvent(event);
    }
}
