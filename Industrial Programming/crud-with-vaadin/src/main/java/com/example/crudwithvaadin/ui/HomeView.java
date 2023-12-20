package com.example.crudwithvaadin.ui;

import com.example.crudwithvaadin.backend.Confectionary;
import com.example.crudwithvaadin.backend.ConfectionaryService;
import com.vaadin.flow.component.html.H1;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.router.Route;
import com.vaadin.flow.server.auth.AnonymousAllowed;
import org.vaadin.crudui.crud.impl.GridCrud;

@Route("")
@AnonymousAllowed
public class HomeView extends VerticalLayout
{
    public HomeView(ConfectionaryService service)
    {
        var crud = new GridCrud<>(Confectionary.class, service);
        crud.getGrid().setColumns("name", "country", "year");
        crud.getCrudFormFactory().setVisibleProperties("name", "country", "year");

        add(new H1 ("Home View"), crud);
    }
}
