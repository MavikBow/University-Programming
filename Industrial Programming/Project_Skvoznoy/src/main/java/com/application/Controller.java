package com.application;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.util.Objects;

public class Controller {

    public File selectedFile;
    public String[] pipeString;
    public Boolean fileChosen = false;

    @FXML
    public Button exitButton = new Button();
    public Label chooseLabel = new Label();
    public Label resultLabel = new Label();
    public CheckBox encryptBox1 = new CheckBox();
    public CheckBox encryptBox2 = new CheckBox();
    public CheckBox zipBox = new CheckBox();
    public RadioButton zipRadar = new RadioButton();
    public RadioButton jarRadar = new RadioButton();
    public RadioButton unZipRadar = new RadioButton();
    public RadioButton unJarRadar = new RadioButton();
    public ImageView resultImage = new ImageView();
    public RadioButton encryptRadar = new RadioButton();
    public RadioButton decryptRadar = new RadioButton();

    @FXML
    private void initialize()
    {
        resultImage.setVisible(false);

        exitButton.setOnAction((ActionEvent event) -> {
            Platform.exit();
        });
        pipeString = new String[4];
    }

    @FXML
    void choosePress()
    {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Choose file");
        selectedFile = fileChooser.showOpenDialog(new Stage());
        if(selectedFile != null)
        {
            chooseLabel.setText(selectedFile.getName());
            pipeString[0] = selectedFile.getName();
            fileChosen = true;
        }
    }

    @FXML
    void encrypt1()
    {
        if(encryptBox1.isSelected()) encryptBox2.setSelected(false);
    }

    @FXML
    void encrypt2()
    {
        if(encryptBox2.isSelected()) encryptBox1.setSelected(false);
    }

    void greenLight()
    {
        resultImage.setImage(new Image(Objects.requireNonNull(getClass().getResourceAsStream("tick.png"))));
        resultImage.setVisible(true);
    }
    void redLight()
    {
       resultImage.setImage(new Image(Objects.requireNonNull(getClass().getResourceAsStream("cross.png"))));
       resultImage.setVisible(true);
    }

    @FXML
    void ProcessAll()
    {
        if(fileChosen) {
            int counter = 1;

            if (encryptBox1.isSelected()) {
                if (encryptRadar.isSelected()) pipeString[counter++] = "-e";
                if (decryptRadar.isSelected()) pipeString[counter++] = "-d";
            }

            if (zipBox.isSelected()) {
                if (zipRadar.isSelected()) pipeString[counter++] = "-z";
                if (jarRadar.isSelected()) pipeString[counter++] = "-j";
                if (unZipRadar.isSelected()) pipeString[counter++] = "-uz";
                if (unJarRadar.isSelected()) pipeString[counter++] = "-uj";
            }

            if (encryptBox2.isSelected()) {
                if (encryptRadar.isSelected()) pipeString[counter++] = "-e";
                if (decryptRadar.isSelected()) pipeString[counter++] = "-d";
            }

            for (int i = 0; i < counter; i++) {
                System.out.print(pipeString[i] + " ");
            }
            System.out.println();
            for (int i = counter; i < 4; i++) {
                pipeString[i] = null;
            }

            resultLabel.setText(BackEnd.processGUI(counter, pipeString));
            greenLight();
        }
        else
        {
            resultLabel.setText("Choose a file!");
            redLight();
        }
    }
}