package com.example.listapp;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class ItemAdapter extends BaseAdapter {
    LayoutInflater m_Inflater;
    String[] items;
    String[] prices;
    String[] descriptions;

    public ItemAdapter(Context context, String[] items, String[] prices, String[] descriptions) {
        this.items = items;
        this.prices = prices;
        this.descriptions = descriptions;
        this.m_Inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        return items.length;
    }

    @Override
    public Object getItem(int i) {
        return items[i];
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {

        View _view = m_Inflater.inflate(R.layout.listview_detail, null);
        TextView nameTextView = (TextView) _view.findViewById(R.id.nameTextView);
        TextView descriptionTextView = (TextView) _view.findViewById(R.id.descriptionTextView);
        TextView priceTextView = (TextView) _view.findViewById(R.id.priceTextView);

        String name = items[i];
        String description = descriptions[i];
        String price = prices[i];

        nameTextView.setText(name);
        descriptionTextView.setText(description);
        priceTextView.setText(price);

        return _view;
    }
}
