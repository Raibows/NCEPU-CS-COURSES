package com.example.test.servicelmpl;

import com.alibaba.fastjson.JSONObject;
import com.example.test.bean.BorrowInfo;
import com.example.test.service.BorrowInfoService;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import lombok.extern.log4j.Log4j2;
import lombok.extern.slf4j.Slf4j;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.awt.print.Pageable;
import java.util.Date;
import java.util.List;


/** 
* BorrowInfoServiceImpl Tester. 
* 
* @author <Authors name> 
* @since <pre>6�� 28, 2020</pre> 
* @version 1.0 
*/ 
@Slf4j
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class BorrowInfoServiceImplTest {

    @Autowired
    private BorrowInfoService borrowInfoService;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: getUnreturnInfo_By_ID(String ID) 
* 
*/ 
@Test
public void testGetUnreturnInfo_By_ID() throws Exception { 
//TODO: Test goes here...
    int pageNum = 1;
    int pageSize = 5;
    PageHelper.startPage(pageNum,pageSize);
    List<BorrowInfo> borrowInfos = borrowInfoService.getUnreturnInfo_By_ID("201709000616");
    PageInfo<BorrowInfo> pageInfos = new PageInfo<BorrowInfo>(borrowInfos);
    PageHelper.clearPage();
    //System.out.println(borrowInfoService.getUnreturnInfo_By_ID("201709000616"));
    //log.info(service.findByIsbn("1234567890123"));
} 

/** 
* 
* Method: getBorrowInfo_By_ID(String ID) 
* 
*/ 
@Test
public void testGetBorrowInfo_By_ID() throws Exception { 
//TODO: Test goes here...
    int pageNum = 1;
    int pageSize = 5;
    PageHelper.startPage(pageNum,pageSize);
    List<BorrowInfo> borrowInfos = borrowInfoService.getUnreturnInfo_By_ID("201709000616");
    PageInfo<BorrowInfo> pageInfos = new PageInfo<BorrowInfo>(borrowInfos);
    PageHelper.clearPage();

} 

/** 
* 
* Method: ReviewBookCondition(String ISBN) 
* 
*/ 
@Test
public void testReviewBookCondition() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.ReviewBookCondition("9876543211234");

} 

/** 
* 
* Method: ReviewBorrConditon(String StuID) 
* 
*/ 
@Test
public void testReviewBorrConditon() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.ReviewBorrConditon("201709000616");
} 

/** 
* 
* Method: BorrowBook(String StuID, String ISBN, Date date) 
* 
*/ 
@Test
public void testBorrowBook() throws Exception { 
//TODO: Test goes here...
    Date date = new Date();
    borrowInfoService.BorrowBook("201709000616","9787301272022",date);
} 

/** 
* 
* Method: SetBorrowedBook(String ISBN) 
* 
*/ 
@Test
public void testSetBorrowedBook() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.SetBorrowedBook("9787301272022");
} 

/** 
* 
* Method: SetBorrowedStudent(String StuID) 
* 
*/ 
@Test
public void testSetBorrowedStudent() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.SetBorrowedStudent("201709000616");
} 

/** 
* 
* Method: ReturnBook(String StuID, String ISBN, Date date) 
* 
*/ 
@Test
public void testReturnBook() throws Exception { 
//TODO: Test goes here...
    Date date = new Date();
    borrowInfoService.ReturnBook("201709000616","9787301272022",date);
} 

/** 
* 
* Method: SetReturnedStudent(String StuID) 
* 
*/ 
@Test
public void testSetReturnedStudent() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.SetReturnedStudent("201709000616");
} 

/** 
* 
* Method: SetReturnedBook(String ISBN) 
* 
*/ 
@Test
public void testSetReturnedBook() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.SetReturnedBook("9787301272022");
} 

/** 
* 
* Method: overdue(String id, String ISBN) 
* 
*/ 
@Test
public void testOverdue() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.overdue("201709000616","9787301272022");
} 

/** 
* 
* Method: getOverdueDays(String id, String ISBN) 
* 
*/ 
@Test
public void testGetOverdueDays() throws Exception { 
//TODO: Test goes here...
    System.out.println(borrowInfoService.getOverdueDays("201709000616","9787301272022"));
} 

/** 
* 
* Method: ReviewReturnStatus(String StuID, String ISBN) 
* 
*/ 
@Test
public void testReviewReturnStatus() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.ReviewReturnStatus("201709000616","9787301272022");
} 

/** 
* 
* Method: ReturnStatus(String StuID, String ISBN) 
* 
*/ 
@Test
public void testReturnStatus() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.ReturnStatus("201709000616","9787301272022");
} 

/** 
* 
* Method: SetPenalty(int days, String stuid) 
* 
*/ 
@Test
public void testSetPenalty() throws Exception { 
//TODO: Test goes here...
    borrowInfoService.SetPenalty(20,"201709000616");
} 


} 
