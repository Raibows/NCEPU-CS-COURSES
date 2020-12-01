package com.example.backstage.Dao.CatalogueDao;

import com.example.backstage.Entity.CatalogueEntity.Donation;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface DonationDao extends JpaRepository<Donation,String> {

    /**
     *
     * @param pageable
     * @return
     */
    Page<Donation> findAll(Pageable pageable);
}
