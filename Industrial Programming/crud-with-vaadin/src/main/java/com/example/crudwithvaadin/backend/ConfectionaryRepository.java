package com.example.crudwithvaadin.backend;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ConfectionaryRepository extends JpaRepository<Confectionary, Integer> {
}
