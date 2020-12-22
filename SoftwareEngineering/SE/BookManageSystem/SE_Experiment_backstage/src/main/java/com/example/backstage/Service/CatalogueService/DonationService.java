package com.example.backstage.Service.CatalogueService;

import com.example.backstage.Dao.CatalogueDao.DonationDao;
import com.example.backstage.Entity.CatalogueEntity.Donation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

@Service
public class DonationService {
    @Autowired
    private DonationDao dao;

    /**
     *
     * @param pageable
     * @return
     */
    public Page<Donation> findAll(Pageable pageable){
        return dao.findAll(pageable);
    }
}
