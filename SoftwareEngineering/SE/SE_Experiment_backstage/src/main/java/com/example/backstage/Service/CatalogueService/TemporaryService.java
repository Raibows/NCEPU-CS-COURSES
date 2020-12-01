package com.example.backstage.Service.CatalogueService;

import com.example.backstage.Dao.CatalogueDao.TemporaryDao;
import com.example.backstage.Entity.CatalogueEntity.Temporary;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;

@Service
@Transactional
public class TemporaryService {
    @Autowired
    private TemporaryDao dao;

    public void addTemporary(Temporary temporary){
        dao.save(temporary);
    }

    public Temporary findByIsbn(String isbn){
        return dao.findByIsbn(isbn);
    }

    public Page<Temporary> findAll(String name,Pageable pageable){
        return dao.findAll(name,pageable);
    }

    public void deleteByIsbn(String isbn){
        dao.deleteByIsbn(isbn);
    }
}
