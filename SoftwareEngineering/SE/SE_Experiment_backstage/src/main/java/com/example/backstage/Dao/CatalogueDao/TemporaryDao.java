package com.example.backstage.Dao.CatalogueDao;

import com.example.backstage.Entity.CatalogueEntity.Temporary;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface TemporaryDao extends JpaRepository<Temporary,String> {
    Temporary findByIsbn(String isbn);

    @Query(value = "select * from temporary_entry where bookName like "+"%"+":name"+"%"+" or isbn like "+"%"+":name"+"%"+
            " or opName like "+"%"+":name"+"%",nativeQuery = true)
    Page<Temporary> findAll(@Param("name")String name, Pageable pageable);

    void deleteByIsbn(String isbn);
}
