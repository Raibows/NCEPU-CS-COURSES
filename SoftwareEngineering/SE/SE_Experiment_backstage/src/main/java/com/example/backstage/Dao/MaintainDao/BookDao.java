package com.example.backstage.Dao.MaintainDao;

import com.example.backstage.Entity.MaintainEntity.Book;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface BookDao extends JpaRepository<Book,String> {
    /**
     *
     * @return
     */
    @Query(value = "select * from bookinfo where bookName like "+"%"+":name"+"%",nativeQuery = true)
    Page<Book> findAllByPage(@Param("name")String name,Pageable pageable);

    /**
     *
     * @return
     */
    @Query(value = "select * from bookinfo where author like "+"%"+":name"+"%",nativeQuery = true)
    Page<Book> findAllByAuthor(@Param("name")String name,Pageable pageable);

    /**
     *
     * @return
     */
    @Query(value = "select * from bookinfo where bookName like "+"%"+":name"+"%"+" or author like "+"%"+":name"+"%"+
            " or type like "+"%"+":name"+"%"+" or isbn like "+"%"+":name"+"%"+" or canBorrow like "+"%"+":name"+"%"+" or publisher like "
            +"%"+":name"+"%"+" or publishDate like "+"%"+":name"+"%",nativeQuery = true)
    Page<Book> findAllByAll(@Param("name")String name,Pageable pageable);


    /**
     *
     * @param isbn
     * @return
     */
    Book findByIsbn(String isbn);

    /**
     *
     * @param isbn
     */
    void deleteByIsbn(String isbn);
}
