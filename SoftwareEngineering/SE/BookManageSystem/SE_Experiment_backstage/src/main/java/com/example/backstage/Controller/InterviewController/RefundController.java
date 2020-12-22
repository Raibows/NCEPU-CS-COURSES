package com.example.backstage.Controller.InterviewController;

import com.example.backstage.Entity.InterviewEntity.Check;
import com.example.backstage.Entity.InterviewEntity.Refund;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.InterviewService.InterviewService;
import com.example.backstage.Service.InterviewService.RefundService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.Date;
import java.util.List;

@Controller
@RequestMapping("/maintain")
@Api("退货")
@CrossOrigin
public class RefundController {
    @Autowired
    private RefundService service;
    @Autowired
    private InterviewService interviewService;

    /**
     *
     * @return
     */
    @RequestMapping(value = "/addRefund",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("新增退货订单")
    @ApiParam(name = "refund",value = "退货信息",required = true)
    public ResultVO addRefund(@RequestBody Refund refund){
        Date date=new Date();
        refund.setOrderDate(date);
        refund.setState(true);
        String isbn=refund.getIsbn();
         try {
             interviewService.deleteByIsbn(isbn);
             service.addRefund(refund);
             return ResultVO.SUCCESS("新增成功!");
         }catch (Exception e){
             return ResultVO.FAIL("新增失败!");
         }
    }

    /**
     *
     * @return
     */
    @RequestMapping(value = "/findAllRefund",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询所有退货订单")
    @ApiParam(name = "all",value = "内容、页数、大小",required = true)
    public ResultVO findAll(@RequestBody JSONObject object){
        String name=object.getAsString("all");
        int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Refund> list=service.findAllByPage(name,pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }
}
