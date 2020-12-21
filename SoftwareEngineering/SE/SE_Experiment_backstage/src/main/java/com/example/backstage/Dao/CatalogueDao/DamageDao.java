package com.example.backstage.Dao.CatalogueDao;

import com.example.backstage.Entity.CatalogueEntity.Damage;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import javax.transaction.Transactional;

@Repository
@Transactional
public interface DamageDao extends JpaRepository<Damage,String> {

    /**
     *
     * @return
     */
    @Query(value = "select * from damage_list where isbn like "+"%"+":name"+"%"+" or bookName like "+"%"+":name"+"%"+
            " or reason like "+"%"+":name"+"%"+" or price like "+"%"+":name"+"%"+" or state like "+"%"+":name"+"%"+" or checker like "
            +"%"+":name"+"%",nativeQuery = true)
    Page<Damage> findAllByAll(@Param("name")String name, Pageable pageable);

    Damage findByIsbn(String isbn);

    void deleteByIsbn(String isbn);
}
