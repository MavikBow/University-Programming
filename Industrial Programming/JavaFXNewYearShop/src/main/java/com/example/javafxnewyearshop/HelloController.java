package com.example.javafxnewyearshop;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.util.ArrayList;

public class HelloController {

    Model model = new Model();
    ObservableList<String> manufacturerList;

    ArrayList<ObservableList<String>> productList = new ArrayList<>();


    @FXML
    private ComboBox manufactureBox = new ComboBox();
    @FXML
    private ComboBox productBox = new ComboBox();
    @FXML
    Button exitButton = new Button();

    @FXML
    private void initialize()
    {
        manufacturerList = FXCollections.observableArrayList(model.nameList);
        manufactureBox.setItems(manufacturerList);
        manufactureBox.setValue("Пусто");

        for(int i = 0; i < model.getManufactureAmount(); i++)
        {
            ObservableList<String> ols = FXCollections.observableArrayList(model.getManufactureList().get(i).nameList);
            productList.add(ols);
        }

        productBox.setValue("Пусто");

        exitButton.setOnAction((ActionEvent event) -> {
            Platform.exit();
        });
    }

    @FXML
    private void manufacturerChoice()
    {
        for(int i = 0; i < model.getManufactureAmount(); i++)
        {
            if(manufactureBox.getValue().equals(model.nameList.get(i)))
            {
                model.getManufactureList().get(i).clearAll();
                model.setManufactureChose(i);
                productBox.setValue("Пусто");
                productBox.setItems(productList.get(i));
            }
        }
    }

    @FXML
    private void productChoice()
    {
        model.setChosenProduct(productBox.getValue().toString());
        updatePrice();
    }

    @FXML
    private TextField priceText = new TextField();

    private void updatePrice()
    {
        priceText.setText(String.format("%.2f", model.price()));
    }

    @FXML
    private void setConcertOn() {
        model.setConcertChosen(true);
        updatePrice();
    }

    @FXML
    private void setConcertOff() {
        model.setConcertChosen(false);
        updatePrice();
    }

    @FXML
    private void setRegularOn()
    {
        model.setIsRegular(true);
        updatePrice();
    }

    @FXML
    private void setRegularOff()
    {
        model.setIsRegular(false);
        updatePrice();
    }
}