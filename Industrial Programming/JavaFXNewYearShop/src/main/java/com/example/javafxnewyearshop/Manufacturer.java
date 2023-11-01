package com.example.javafxnewyearshop;

import java.util.ArrayList;
import java.util.Scanner;

public class Manufacturer {
    public String name;
    public int amount;
    public ArrayList<Item> list;
    public boolean chosen;

    public Manufacturer(Scanner sc) throws Exception {
        this.chosen = false;
        this.read(sc);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public class Item{
        public String name;
        public int price;
        public boolean marked;

        public Item(String name, int price) {
            this.name = name;
            this.price = price;
            this.marked = false;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public int getPrice() {
            return price;
        }

        public void setPrice(int price) {
            this.price = price;
        }

        public boolean isMarked() {
            return marked;
        }

        public void setMarked(boolean marked) {
            this.marked = marked;
        }
    }

    public void read(Scanner sc) throws Exception {
        name = new String(sc.nextLine());
        amount = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < amount; i++) {
            String[] line = sc.nextLine().split("\\s+");
            list.add(new Item(line[0], Integer.parseInt(line[1])));
        }
    }

    public int getPriceOverall()
    {
        int price = 0;
        for(int i = 0; i < amount; i ++) {
            if (list.get(i).isMarked()) {
                price += list.get(i).getPrice();
            }
        }
        return price;
    }
}
