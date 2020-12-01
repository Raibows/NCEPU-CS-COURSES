package com.example.backstage.Service.CatalogueService;

import com.example.backstage.Entity.CatalogueEntity.Damage;
import com.example.backstage.ResultVO;
import lombok.extern.log4j.Log4j2;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import java.math.BigDecimal;

/** 
* DamageService Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class DamageServiceTest {
    @Autowired
    private DamageService service;

@Before
public void before() throws Exception {
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: addDamage(Damage damage) 
* 
*/ 
@Test
public void testAddDamage() throws Exception { 
//TODO: Test goes here...
    Damage damage=new Damage("1234567891567","afe","书籍破损",new BigDecimal(40),false,
            "luo");
    service.addDamage(damage);
} 

/** 
* 
* Method: findAll(String name, Pageable pageable) 
* 
*/ 
@Test
public void testFindAll() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<Damage> list= service.findAll("",pageable);
    log.info(list.getContent());
} 

/** 
* 
* Method: findByIsbn(String isbn) 
* 
*/ 
@Test
public void testFindByIsbn() throws Exception { 
//TODO: Test goes here...
    log.info(service.findByIsbn("9781491939369"));
} 

/** 
* 
* Method: deleteByIsbn(String isbn) 
* 
*/ 
@Test
public void testDeleteByIsbn() throws Exception { 
//TODO: Test goes here...
    service.deleteByIsbn("1234567891567");
} 


} 
