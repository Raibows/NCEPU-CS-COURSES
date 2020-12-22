package com.example.backstage.Service.MatainService;

import com.example.backstage.Dao.MaintainDao.BookDao;
import com.example.backstage.Entity.MaintainEntity.Book;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;


import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class BookService {
    @Autowired
    BookDao bookDao;

    /**
     *
     * @return
     */
    public Page<Book> findAllByPage(String name,Pageable pageable){
        return bookDao.findAllByPage(name,pageable);
    }


    /**
     *
     * @param book
     */
    public void updateBook(Book book){
        bookDao.save(book);
    }


    /**
     *
     * @return
     */
    public Page<Book> findAllByAuthor(String name,Pageable pageable){
        return bookDao.findAllByAuthor(name,pageable);
    }

    /**
     *
     * @return
     */
    public Page<Book> findAllByAll(String name,Pageable pageable){
        return bookDao.findAllByAll(name,pageable);
    }


    public Book findByIsbn(String isbn){
        return bookDao.findByIsbn(isbn);
    }

    public void deleteByIsnb(String isbn){
        bookDao.deleteByIsbn(isbn);
    }

}
