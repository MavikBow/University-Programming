package com.example.crudwithvaadin.backend;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.vaadin.crudui.crud.CrudListener;

import java.util.List;

@Service
@RequiredArgsConstructor
public class ConfectionaryService implements CrudListener<Confectionary>
{
    private final ConfectionaryRepository repository;
    
    @Override
    public List<Confectionary> findAll()
    {
        return repository.findAll();
    }

    @Override
    public Confectionary add(Confectionary confectionary)
    {
        return repository.save(confectionary);
    }

    @Override
    public Confectionary update(Confectionary confectionary)
    {
        return repository.save(confectionary);
    }

    @Override
    public void delete(Confectionary confectionary)
    {
        repository.delete(confectionary);
    }
}
