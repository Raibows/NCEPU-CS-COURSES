package com.example.backstage.Service.CatalogueService;

import com.example.backstage.Dao.CatalogueDao.DamageDao;
import com.example.backstage.Entity.CatalogueEntity.Damage;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

@Service
public class DamageService {
    @Autowired
    private DamageDao dao;

    public void addDamage(Damage damage){
        dao.save(damage);
    }

    public Page<Damage> findAll(String name, Pageable pageable){
        return dao.findAllByAll(name,pageable);
    }

    public Damage findByIsbn(String isbn){
        return dao.findByIsbn(isbn);
    }

    public void deleteByIsbn(String isbn){
        dao.deleteByIsbn(isbn);
    }
}
