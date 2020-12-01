package com.example.backstage.Dao.InterviewDao;

import com.example.backstage.Entity.InterviewEntity.Interview;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface InterviewDao extends JpaRepository<Interview,String> {

    /**
     *
     * @param id
     * @return
     */
    Interview findInterviewById(String id);

    /**
     *
     * @param pageable
     * @return
     */
    @Query(value = "SELECT interviewlist.id,userId,bookSeller,price,orderDate,isbn,bookName,num,u.name from interviewlist JOIN user u on u.id=interviewlist.userId where bookName like "
            +"%"+":name"+"%"+" or interviewlist.id like "+"%"+":name"+"%"+
            " or userId like "+"%"+":name"+"%"+" or bookSeller like "+"%"+":name"+"%"+" or price like "+"%"+":name"+"%"+" or bookName like "
            +"%"+":name"+"%"+" or isbn like "+"%"+":name"+"%",
             countQuery = "SELECT count(*) from interviewlist JOIN user u on u.id=interviewlist.userId where bookName like "
                     +"%"+":name"+"%"+" or interviewlist.id like "+"%"+":name"+"%"+
                     " or userId like "+"%"+":name"+"%"+" or bookSeller like "+"%"+":name"+"%"+" or price like "+"%"+":name"+"%"+" or bookName like "
                     +"%"+":name"+"%"+" or isbn like "+"%"+":name"+"%"
            ,nativeQuery = true)
    Page<Interview> findAllByAll(@Param("name")String name,Pageable pageable);

    /**
     *
     * @param id
     */
    void deleteById(String id);

    /**
     *
     * @param isbn
     */
    void deleteByIsbn(String isbn);

}
